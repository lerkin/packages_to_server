#include "pch.h"
#include "resp_db.h"

std::string resp_db::getGUID()
{
	return xg::newGuid().str();
}

// ---------------------------------------------------------------------------
std::string archfile::datetime()
{
	return file_datetime::GetDatetime(std::localtime(&fdatetime));
}

// ---------------------------------------------------------------------------
prepared_statement_query_ptr resp_db::createInsertPtr(const std::string& _query_text)
{
	std::string pfx{ "INSERT INTO resp_db." };
	pfx.append(_query_text);

	return std::make_shared<PreparedStatementQuery>(pfx);
}

bool resp_db::checkCatalog(const std::string& name, const std::string& code)
{
	std::stringstream query;
	query << "SELECT 1 FROM catalogues." << name << " WHERE code = '" << code << "'";

	if (session->executeQuery(query.str())->rowsCount())
		return true;

	return false;
}

// ---------------------------------------------------------------------------
void resp_db::insertListContent(archfile& file)
{
	psInsertListForRating->setString(2, file.GUID);
	psInsertListForRating->setString(3, file.fname);
	psInsertListForRating->setString(4, file.datetime());
	psInsertListForRating->setUInt(	 5, file.fsize);
	psInsertListForRating->setUInt(	 6, file.fcrc);
	psInsertListForRating->setNull(	 7, sql::DataType::VARCHAR);

	std::stringstream filename{ file.fname };

	std::string prefix, record_type, category;
	std::getline(filename, prefix, '_');
	std::getline(filename, record_type, '_');

	if (record_type == "landRecord")
	{
		std::getline(filename, category, '_');

		if (checkCatalog("categories_v01", category))
			psInsertListForRating->setString(7, category);
		else
			throw ListForRatingException(1060);
	}

	std::getline(filename, file.GUID, '.');
	psInsertListForRating->setString(1, file.GUID);
	psInsertListForRating->executeUpdate();

	auto document{ new pugi::xml_document };
	if (document->load_buffer(file.fcontent, file.fsize).status != pugi::status_ok)
		throw ListForRatingException(2);

	auto root_node{ document->first_child() };
	auto nodeName{ root_node.name() };

	if (std::string(nodeName) != "ListForRating")
		throw ListForRatingException(3);

	if (std::distance(root_node.attributes().begin(), root_node.attributes().end()) != 1)
		throw ListForRatingException(45);

	LFRTraits* list{ nullptr };

	switch (std::stoi(root_node.attributes().begin()->value()))
	{
	//case 3:
	//	list = new LFR03::ListForRating;
	//	break;

	case 4:
		list = new LFR04::ListForRating;
		break;

	case 5:
		list = new LFR05::ListForRating;
		break;

	default:
		throw ListForRatingException(45);
	}

	list->parse(document);
	list->insert(file.GUID);

	delete list;
}

void resp_db::insertGeometryContent(archfile& file)
{
	__GUID GUID{ getGUID(), "" };

	psInsertListForRating->setString(1, GUID.first);							// GUID
	psInsertListForRating->setString(2, file.GUID);								// ParentGUID
	psInsertListForRating->setString(3, file.fname);							// FileName
	psInsertListForRating->setString(4, file.datetime());					// FileDateTime
	psInsertListForRating->setUInt(	 5, file.fsize);							// FileSize
	psInsertListForRating->setUInt(	 6, file.fcrc);								// CRC
	psInsertListForRating->setNull(	 7, sql::DataType::VARCHAR);	// Category
	psInsertListForRating->executeUpdate();

	auto tempZipDirectory = fs::temp_directory_path() / file.fname;
	fs::create_directory(tempZipDirectory);

	auto tempZipFilename = tempZipDirectory / file.fname;

	std::ofstream tempZipFile(tempZipFilename, std::ios_base::binary);
	tempZipFile.write((char*)file.fcontent, file.fsize);
	tempZipFile.close();

	lzpp::ZipArchive GeometryFile(tempZipFilename.string());
	if (not GeometryFile.open())
	{
		wxString message;
		message.append("Ошибка открытия файла: ");
		message.append(tempZipDirectory.filename().string());

		wxMessageBox(message, "Ошибка доступа к файлу", wxOK | wxICON_ERROR);
		return;
	}

	auto tempMapInfoDirectory = tempZipDirectory / tempZipDirectory.stem();
	fs::create_directory(tempMapInfoDirectory);

	for (auto& fileEntry : GeometryFile.getEntries())
	{
		std::ofstream tempMapInfoFile(tempMapInfoDirectory / fileEntry.getName(), std::ios_base::binary);
		tempMapInfoFile.write((char*)fileEntry.readAsBinary(), fileEntry.getSize());
		tempMapInfoFile.close();
	}

	GUID.second = tempZipDirectory.stem().string();
	std::replace(GUID.second.begin(), GUID.second.end(), '_', ':');

	InsertSpatialData(GUID, tempMapInfoDirectory);

	fs::remove_all(tempZipDirectory);
}

void resp_db::InsertSpatialData(const __GUID& GUID, const fs::path& mapInfoDirectory)
{
	auto MapInfoDS = (GDALDataset*) GDALOpenEx(mapInfoDirectory.string().c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);

	psInsertCadastralGeometry->setString(1, GUID.first);
	psInsertCadastralGeometry->setString(2, GUID.second);

	for (auto Layer : MapInfoDS->GetLayers())
	{
		for (auto& LayerFeature : Layer)
		{
			psInsertCadastralGeometry->setNull( 3, sql::DataType::INTEGER);		// ID
			psInsertCadastralGeometry->setNull( 4, sql::DataType::VARCHAR);		// Label
			psInsertCadastralGeometry->setNull( 5, sql::DataType::VARCHAR);		// Note
			psInsertCadastralGeometry->setNull( 6, sql::DataType::GEOMETRY);	// Points
			psInsertCadastralGeometry->setNull( 7, sql::DataType::GEOMETRY);	// Lines
			psInsertCadastralGeometry->setNull( 8, sql::DataType::GEOMETRY);	// Polygons
			psInsertCadastralGeometry->setNull( 9, sql::DataType::VARCHAR);		// Pen
			psInsertCadastralGeometry->setNull(10, sql::DataType::VARCHAR);		// Brush
			psInsertCadastralGeometry->setNull(11, sql::DataType::VARCHAR);		// Center
			psInsertCadastralGeometry->setNull(12, sql::DataType::CHAR);			// Smooth

			for (auto&& Field : LayerFeature)
			{
				switch (Field.GetIndex())
				{
				case 0:	// ID
					if (not Field.empty())
						psInsertCadastralGeometry->setUInt(3, Field.GetAsInteger());
					break;
				case 1:	// Label
					if (not Field.empty())
						psInsertCadastralGeometry->setString(4, Field.GetAsString());
					break;
				case 2:	// Note
					if (not Field.empty())
						psInsertCadastralGeometry->setString(5, Field.GetAsString());
					break;
				}
			}

			for (int iGeomField = 0; iGeomField < LayerFeature->GetGeomFieldCount(); iGeomField++)
			{
				auto Geometry = LayerFeature->GetGeomFieldRef(iGeomField);
				
				if (not Geometry->IsEmpty())
				{
					auto wktString = Geometry->exportToWkt();
					std::istringstream wktStringStream(wktString);

					switch (wkbFlatten(Geometry->getGeometryType()))
					{
					case wkbPoint:			// Points
						psInsertCadastralGeometry->setString(6, wktString);
						break;
					case wkbLineString:	// Lines
						psInsertCadastralGeometry->setString(7, wktString);
						break;
					case wkbPolygon:		// Polygons
						psInsertCadastralGeometry->setString(8, wktString);
						break;
					}
				}
			}
			
			psInsertCadastralGeometry->executeUpdate();
			session->execute("COMMIT");
		}
	}

	GDALClose(MapInfoDS);
}

// ---------------------------------------------------------------------------
void resp_db::insert_package(const wxString& filename)
{
	fs::path filepath{ std::string(filename) };
	auto packageFilename{ filepath.filename().string() };
	auto packageDateTime{ file_datetime::GetDatetime(filepath) };
	auto packageFileSize{ fs::file_size(filepath) };
	auto packageContent = std::make_unique<char[]>(packageFileSize);

	std::ifstream infile(std::string(filename), std::ios_base::binary);
	infile.read(packageContent.get(), packageFileSize);
	infile.close();

	lzpp::ZipArchive package(filename.utf8_string());
	if (not package.open())
	{
		wxString message;
		message.append("Ошибка открытия файла: ");
		message.append(filepath.filename().string());

		wxMessageBox(message, "Ошибка доступа к файлу", wxOK | wxICON_ERROR);
		return;
	}

	auto Off{ packageFilename.find("list") + 5 };
	auto Count{ packageFilename.find(".zip") - Off };

	if (Count != 36)
		return;

	__GUID GUID	{
		packageFilename.substr(Off, Count),
		packageFilename
	};

	membuf packageStreamBuffer(packageContent.get(), packageContent.get() + packageFileSize);
	std::istream packageContentStream(&packageStreamBuffer);

	psInsertList->setString(1, GUID.first);
	psInsertList->setString(2, GUID.second);
	psInsertList->setString(3, packageDateTime);
	psInsertList->setUInt(	4, packageFileSize);
	psInsertList->setBlob(	5, &packageContentStream);
	psInsertList->executeUpdate();

 	for (auto& it : package.getEntries())
	{
		filepath = fs::path(it.getName());

		archfile file{
			GUID.first,
			filepath.filename().string(),
			it.getSize(),
			it.getDate(),
			it.getCRC(),
			it.readAsBinary()
		};

		auto ext = filepath.extension();

		if (ext == ".xml")
			insertListContent(file);
		else if (ext == ".zip")
			insertGeometryContent(file);
	}

	package.close();
}
