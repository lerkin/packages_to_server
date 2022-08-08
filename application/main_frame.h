#pragma once
#include "file_datetime.h"
#include "resp_db.h"

class AppForm
	: public wxFrame
{
	using pWxMenuBar = wxMenuBar*;
	using pWxMenu = wxMenu*;
	using pWxMenuItem = wxMenuItem*;
	using pWxRichTextCtrl = wxRichTextCtrl*;

public:
	AppForm(wxWindow*, wxWindowID);
	~AppForm();
	
	void MakeMainMenu();
	void LoadZipPackage();
	void LoadPackages();
//	void LoadSoilCard();
//	void LoadGNPSDB();
	
protected:
	pWxMenuBar menuBar;
	pWxMenu mbFile, mbHelp;

	pWxRichTextCtrl console;

	void OnFileMenu(wxCommandEvent&);
	void OnAppMenu(wxCommandEvent&);

	DECLARE_EVENT_TABLE()
};

using pAppForm = AppForm*;
