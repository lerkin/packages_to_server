#include "pch.h"
#include "loadXML.h"

mysql_session_ptr session;

sql::ConnectOptionsMap writeConnectionOptions
{
  {OPT_HOSTNAME,              "tcp://127.0.0.1"},
  {OPT_PORT,                  3306},
  {OPT_USERNAME,              "root"},
  {OPT_PASSWORD,              "es1841"},
  {OPT_CHARSET_NAME,          "utf8mb4"},
  {OPT_CHARACTER_SET_RESULTS, "cp1251"}
};

bool Application::OnInit()
{
  session = std::make_unique<mysql_session>(writeConnectionOptions);

  mainForm = new AppForm(nullptr, wxID_ANY);
  return mainForm->Show();
}

int Application::OnExit()
{
  return EXIT_SUCCESS;
}

IMPLEMENT_APP(Application)
