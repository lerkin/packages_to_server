#pragma once

class file_datetime
{
	static std::tm* GetNodeDatetime(const fs::path&);

public:
	static std::string GetDate(const fs::path&);
	static std::string GetDate(const std::tm*);
	static std::string GetTime(const fs::path&);
	static std::string GetTime(const std::tm*);
	static std::string GetDatetime(const fs::path&);
	static std::string GetDatetime(const std::tm*);
};
