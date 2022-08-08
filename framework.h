#pragma once
#pragma warning( disable : 4245 4505 4996 5054 26812 28251 )
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <array>
#include <ctime>
#include <chrono>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <charconv>
#include <exception>
#include <algorithm>
#include <filesystem>

#define WXUSINGDLL
#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/grid.h>
#include <wx/mstream.h>
#include <wx/richtext/richtextctrl.h>

#include "mysql_session.h"

#include <ogrsf_frmts.h>
#include <crossguid/guid.hpp>
#include <pugixml.hpp>
#include <libzippp/libzippp.h>

#include <cvt_utils.hpp>

namespace fs      = std::filesystem;
namespace lzpp    = libzippp;
namespace chrono  = std::chrono;

