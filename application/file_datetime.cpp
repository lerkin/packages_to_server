#include <pch.h>
#include "file_datetime.h"

std::tm* file_datetime::GetNodeDatetime(const fs::path& filename)
{
	auto filetime = fs::last_write_time(filename);
	auto time_now = chrono::system_clock::now().time_since_epoch();
	auto seconds	= fs::file_time_type::clock::now().time_since_epoch() - time_now;
	auto elapse		= chrono::duration_cast<chrono::seconds>(seconds).count();
	auto sys_time = chrono::duration_cast<chrono::seconds>(filetime.time_since_epoch()).count() - elapse;

	return std::localtime(&sys_time);
}

std::string file_datetime::GetDate(const fs::path& filename)
{
	return GetDate(GetNodeDatetime(filename));
}

std::string file_datetime::GetDate(const std::tm* p)
{
	std::string oss("0000-00-00");
	auto ptr = oss.data();

	int year = p->tm_year + 1900;
	int month = p->tm_mon + 1;

	std::to_chars(ptr, ptr + 4, year);
	std::to_chars(ptr + (month > 9 ? 5 : 6), ptr + 7, month);
	std::to_chars(ptr + (p->tm_mday > 9 ? 8 : 9), ptr + 10, p->tm_mday);

	return oss;
}

std::string file_datetime::GetTime(const fs::path& filename)
{
	return GetTime(GetNodeDatetime(filename));
}

std::string file_datetime::GetTime(const std::tm* p)
{
	std::string oss("00:00:00");
	auto ptr = oss.data();

	std::to_chars(ptr + (p->tm_hour > 9 ? 0 : 1), ptr + 2, p->tm_hour);
	std::to_chars(ptr + (p->tm_min  > 9 ? 3 : 4), ptr + 5, p->tm_min);
	std::to_chars(ptr + (p->tm_sec  > 9 ? 6 : 7), ptr + 8, p->tm_sec);

	return oss;
}

std::string file_datetime::GetDatetime(const fs::path& filename)
{
	auto p = GetNodeDatetime(filename);
	return GetDate(p) + ' ' + GetTime(p);
}

std::string file_datetime::GetDatetime(const std::tm* p)
{
	return GetDate(p) + ' ' + GetTime(p);
}
