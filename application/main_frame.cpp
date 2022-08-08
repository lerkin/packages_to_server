#include <pch.h>
#include "main_frame.h"
#include "rc.h"

AppForm::AppForm(wxWindow* parent, wxWindowID id)
	: wxFrame(parent, id, wxT("Загрузка XML-пакетов"))
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

	pWxMenuItem mbFileOpen	= new wxMenuItem(mbFile,	0x3000,			wxT("&Загрузка..."));
	pWxMenuItem mbFilePack	= new wxMenuItem(mbFile,	0x3001,			wxT("&Пакетная загрузка..."));
	pWxMenuItem mbFileSoil	= new wxMenuItem(mbFile,	0x3002,			wxT("Загрузка &почвенной карты"));
	pWxMenuItem mbFileGNPS	= new wxMenuItem(mbFile,	0x3003,			wxT("Загрузка базы по СНТ"));
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
template <typename _Ty>
void AppForm::LoadPackages(std::shared_ptr<_Ty> dialog)
{
	wxString sourceName;

	if (wxID_OK == dialog->ShowModal())
		sourceName = dialog->GetPath();
	else
		return;

	try
	{
		if constexpr (std::is_same_v<_Ty, wxFileDialog>)
		{
			resp_db db;
			db.insert_package(sourceName);
		}
		else if constexpr (std::is_same_v<_Ty, wxDirDialog>)
		{
			for (auto& entry : fs::directory_iterator(fs::path(sourceName.ToStdString())))
			{
				resp_db db;
				db.insert_package(entry.path().c_str());
			}
		}
	}
	catch (sql::SQLException& err)
	{
		std::ostringstream message;
		message << "SQLSTATE [" << err.getSQLState() << "]: General error #" << err.getErrorCode() << ": " << err.what() << std::endl;
		wxMessageBox(message.str(), "MySQL Connector error", wxICON_ERROR | wxCLOSE);
		session->execute("ROLLBACK");
	}
	catch (ListForRatingException& err)
	{
		wxMessageBox(wxString(err.what()), err.what_code());
		session->execute("ROLLBACK");
	}
}

// ---------------------------------------------------------------------------
void AppForm::OnFileMenu(wxCommandEvent& event)
{
	event.Skip();

	switch (event.GetId())
	{
	case 0x3000:
		LoadPackages(std::make_shared<wxFileDialog>(this));
		break;
	case 0x3001:
		LoadPackages(std::make_shared<wxDirDialog>(this));
		break;
	case 0x3002:
	case 0x3003:
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
EVT_MENU(0x3000,			AppForm::OnFileMenu)
EVT_MENU(0x3001,			AppForm::OnFileMenu)
EVT_MENU(0x3002,			AppForm::OnFileMenu)
EVT_MENU(0x3003,			AppForm::OnFileMenu)
EVT_MENU(wxID_EXIT,		AppForm::OnFileMenu)
EVT_MENU(wxID_HELP,		AppForm::OnAppMenu)
EVT_MENU(wxID_ABOUT,	AppForm::OnAppMenu)
END_EVENT_TABLE()
