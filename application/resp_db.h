#pragma once
#include "file_datetime.h"
#include "ListForRating_v04.h"
#include "ListForRating_v05.h"
#include "ListforRating_except.h"

class resp_db
{
	// --------------------------------------------------------------------------
	prepared_statement_query_ptr psInsertList;
	prepared_statement_query_ptr psInsertListForRating;
	prepared_statement_query_ptr psInsertCadastralGeometry;

	struct membuf : std::streambuf
	{
		membuf(char* begin, char* end) {
			this->setg(begin, begin, end);
		}
	};

	// --------------------------------------------------------------------------
	typedef std::pair<std::string, std::string> __GUID;
	typedef const __GUID& __GUID_cref;
	typedef std::unique_ptr<pugi::xml_document> xml_document_ptr;
	
	// --------------------------------------------------------------------------
	std::string getGUID();
	prepared_statement_query_ptr createInsertPtr(const std::string&);
	bool checkCatalog(const std::string&, const std::string&);

	// --------------------------------------------------------------------------
	void insertListContent(archfile&);
	void insertGeometryContent(archfile&);
	void InsertSpatialData(const __GUID&, const fs::path&);

public:
	resp_db()
	{
		psInsertList = createInsertPtr("\
			_list(GUID, FileName, FileDateTime, FileSize, FileContent)\
				VALUE(?, ?, ?, ?, ?)");

		psInsertListForRating = createInsertPtr("\
			_list_for_rating(GUID, ParentGUID, FileName, FileDate, FileSize, FileCRC, Category)\
				VALUE (?, ?, ?, ?, ?, (SELECT HEX(?)), ?)");

		psInsertCadastralGeometry = createInsertPtr("\
			cadastral_geometry(GUID, CadastralNumber, `ID`, `Label`, `Note`, `Points`, `Lines`, `Polygons`, `Pen`, `Brush`, `Center`, `Smooth`)\
				VALUE(?, ?, ?, ?, ?, ?, ?, ST_GeomFromText(?), ?, ?, ?, ?)");
	}

	~resp_db()
	{
		psInsertList->close();
		psInsertListForRating->close();
		psInsertCadastralGeometry->close();
	}

	void insert_package(const wxString&);
};
