#pragma once
#include "main_frame.h"

class Application
  : public wxApp
{
  using base_class = wxApp;

protected:
  pAppForm mainForm{ nullptr };

public:
  Application();
  virtual ~Application();

  virtual bool OnInit() wxOVERRIDE;
  virtual  int OnExit() wxOVERRIDE;
};

DECLARE_APP(Application)
