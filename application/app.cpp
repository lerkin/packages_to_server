#include "pch.h"
#include "app.h"

Application::Application()
  : base_class()
{
  GDALAllRegister();
  wxImage::AddHandler(new wxPNGHandler);
}

Application::~Application()
{
  wxImage::CleanUpHandlers();
}
