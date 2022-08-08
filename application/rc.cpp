#include "pch.h"
#include "rc.h"

namespace rc
{
  wxImage GetPngImage(UINT uID, HMODULE hModule)
  {
    auto resource = ::FindResource(hModule, MAKEINTRESOURCE(uID), L"PNG");
    wxMemoryInputStream inputStream(::LoadResource(hModule, resource), ::SizeofResource(hModule, resource));

    return wxImage(inputStream, wxBITMAP_TYPE_PNG);
  }
}
