#include "pch.h"
#include "main_frame.h"
//#include "mi.h"
#include "rc.h"

AppForm::AppForm(wxWindow* parent, wxWindowID id)
	: wxFrame(parent, id, "Загрузка XML-пакетов")
{
	SetSizeHints(wxDefaultSize, wxDefaultSize);
	MakeMainMenu();
	Centre(wxBOTH);
}

AppForm::~AppForm()
{}

// ---------------------------------------------------------------------------
void AppForm::MakeMainMenu()
{
	menuBar = new wxMenuBar(0);
	mbFile = new wxMenu();
	mbHelp = new wxMenu();

	pWxMenuItem mbFileOpen	= new wxMenuItem(mbFile,	wxID_OPEN,	wxT("&Загрузка..."));
	pWxMenuItem mbFilePack	= new wxMenuItem(mbFile,	0x3001,			wxT("&Пакетная загрузка..."));
	pWxMenuItem mbFileSoil	= new wxMenuItem(mbFile,	0x3000,			wxT("Загрузка &почвенной карты"));
	pWxMenuItem mbFileGNPS	= new wxMenuItem(mbFile,	0x3002,			wxT("Загрузка базы по СНТ"));
	pWxMenuItem mbFileExit	= new wxMenuItem(mbFile,	wxID_EXIT,	wxT("В&ыход"));
	pWxMenuItem mbHelpHelp	= new wxMenuItem(mbHelp,	wxID_HELP,	wxT("&Помощь"));
	pWxMenuItem mbHelpAbout = new wxMenuItem(mbHelp,	wxID_ABOUT, wxT("&О программе..."));

	mbFileOpen->SetBitmap(rc::GetPngImage(IDB_MENU_FILE_OPEN));
	mbFileExit->SetBitmap(rc::GetPngImage(IDB_MENU_FILE_EXIT));
	mbHelpAbout->SetBitmap(rc::GetPngImage(IDB_MENU_APP_ABOUT));

	mbFile->Append(mbFileOpen);
	mbFile->Append(mbFilePack);
	mbFile->Append(mbFileSoil);
	mbFile->Append(mbFileGNPS);
	mbFile->AppendSeparator();
	mbFile->Append(mbFileExit);
	menuBar->Append(mbFile, wxT("&Файл"));

	mbHelp->Append(mbHelpHelp);
	mbHelp->AppendSeparator();
	mbHelp->Append(mbHelpAbout);
	menuBar->Append(mbHelp, wxT("&Справка"));

	SetMenuBar(menuBar);

	// console
	SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1{ new wxBoxSizer(wxVERTICAL) };
	console = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
		0 | wxVSCROLL | wxHSCROLL | wxBORDER_SIMPLE | wxWANTS_CHARS);
	bSizer1->Add(console, 1, wxEXPAND | wxALL, 5);

	SetSizer(bSizer1);
	Layout();

	Centre(wxBOTH);
}

// ---------------------------------------------------------------------------
void AppForm::LoadZipPackage()
{
	wxString filename;

	auto openFileDialog{ new wxFileDialog(this) };
	if (wxID_OK == openFileDialog->ShowModal())
		filename = openFileDialog->GetPath();

	delete openFileDialog;

	if (filename.empty())
		return;

	try {
		session->execute("START TRANSACTION");
		resp_db db;
		db.insert_package(filename);
		session->execute("COMMIT");
	}
	catch (sql::SQLException& err)
	{
		std::ostringstream message;
		message << "SQLSTATE[" << err.getSQLState() << "]: General error #" << err.getErrorCode() << ": " << err.what() << std::endl;
		wxMessageBox(message.str(), "MySQL Connector error", wxICON_ERROR | wxCLOSE);
	}
	catch (ListForRatingException& err)
	{
		wxMessageBox(wxString(err.what()), err.what_code());
		session->execute("ROLLBACK");
	}
}

void AppForm::LoadPackages()
{
	wxString directory;

	auto openDirectory{ new wxDirDialog(this) };
	if (wxID_OK == openDirectory->ShowModal())
		directory = openDirectory->GetPath();

	delete openDirectory;

	if (directory.empty())
		return;

	for (auto entry : fs::directory_iterator(fs::path(std::string(directory))))
	{
		console->WriteText(entry.path().c_str());
		console->Newline();

		try
		{
			resp_db db;
			session->execute("START TRANSACTION");
			db.insert_package(entry.path().c_str());
			session->execute("COMMIT");
		}
		catch (sql::SQLException& err)
		{
			std::ostringstream message;
			message << "SQLSTATE[" << err.getSQLState() << "]: General error #" << err.getErrorCode() << ": " << err.what() << std::endl;
			wxMessageBox(message.str(), "MySQL Connector error", wxICON_ERROR | wxCLOSE);
			session->execute("ROLLBACK");
		}
		catch (ListForRatingException& err)
		{
			wxMessageBox(wxString(err.what()), err.what_code());
			session->execute("ROLLBACK");
		}
	}
}
/*
void AppForm::LoadSoilCard()
{
	wxString filename;

	auto openFileDialog{ new wxFileDialog(this) };
	if (wxID_OK == openFileDialog->ShowModal())
		filename = openFileDialog->GetPath();

	delete openFileDialog;

	if (filename.empty())
		return;

	fs::path file{ std::string(filename) };
	fs::current_path(file.parent_path());

	mid_mif_data data(file.stem());
	mid_mif fn(std::string((const char* const)data.mid_file.ptr, data.mid_file.size),
						 std::string((const char* const)data.mif_file.ptr, data.mif_file.size));

	auto query = session->prepareStatement("\
		INSERT INTO soil_db.map(ID, SoilContourNum, SoilCode, SoilIndex, TabNum, SoilVarietyNum, Data)\
			VALUE(?, ?, ?, ?, ?, ?, ?)");

	for (auto& region : fn.Data)
	{
		query->setNull(1, sql::DataType::INTEGER);	// ID
		query->setNull(2, sql::DataType::INTEGER);	// SoilContourNum
		query->setNull(3, sql::DataType::INTEGER);	// SoilCode
		query->setNull(4, sql::DataType::VARCHAR);	// SoilIndex
		query->setNull(5, sql::DataType::INTEGER);	// TabNum
		query->setNull(6, sql::DataType::INTEGER);	// SoilVarietyNum
		query->setNull(7, sql::DataType::GEOMETRY);	// Data

		if (not region->desc[0].empty())	// ID
			query->setUInt(1, std::stoul(region->desc[0]));

		if (not region->desc[1].empty())	// SoilContourNum
			query->setUInt(2, std::stoul(region->desc[1]));
		
		if (not region->desc[2].empty())	// SoilCode
			query->setUInt(3, std::stoul(region->desc[2]));

		if (not region->desc[3].empty())	// SoilIndex
			query->setString(4, cp1251_to_utf8(region->desc[3]));
		
		if (not region->desc[9].empty())	// TabNum
			query->setUInt(5, std::stoul(region->desc[9]));

		if (not region->desc[10].empty())	// SoilVarietyNum
			query->setInt(6, std::stoul(region->desc[10]));

		if (region->type == ST_GEOMETRY::KeywordHash("REGION"))
		{
			std::string geom_query("SELECT ST_GeomFromText(\"");
			geom_query.append(region->geom->getGeomText());
			geom_query.append("\")");

			auto result{ session->executeQuery(geom_query) };
			result->first();

			query->setBlob(7, result->getBlob(1));
		}
		query->executeUpdate();
	}
}
*/
void AppForm::LoadGNPSDB()
{
	//wxString filename;

	//auto openFileDialog{ new wxFileDialog(this) };
	//if (wxID_OK == openFileDialog->ShowModal())
	//	filename = openFileDialog->GetPath();

	//delete openFileDialog;
}

// ---------------------------------------------------------------------------
void AppForm::OnFileMenu(wxCommandEvent& event)
{
	event.Skip();

	switch (event.GetId())
	{
	case wxID_OPEN:
		LoadZipPackage();
		break;
	case 0x3000:
//		LoadSoilCard();
		break;
	case 0x3001:
		LoadPackages();
		break;
	case 0x3002:
		LoadGNPSDB();
		break;
	case wxID_EXIT:
		Close();
		break;
	}
}

void AppForm::OnAppMenu(wxCommandEvent& event)
{
	event.Skip();

	switch (event.GetId())
	{
	case wxID_HELP:
		break;
	case wxID_ABOUT:
		break;
	}
}

// ---------------------------------------------------------------------------
BEGIN_EVENT_TABLE(AppForm, wxFrame)
EVT_MENU(wxID_OPEN,		AppForm::OnFileMenu)
EVT_MENU(0x3000,			AppForm::OnFileMenu)
EVT_MENU(0x3001,			AppForm::OnFileMenu)
EVT_MENU(wxID_EXIT,		AppForm::OnFileMenu)
EVT_MENU(wxID_HELP,		AppForm::OnAppMenu)
EVT_MENU(wxID_ABOUT,	AppForm::OnAppMenu)
END_EVENT_TABLE()
