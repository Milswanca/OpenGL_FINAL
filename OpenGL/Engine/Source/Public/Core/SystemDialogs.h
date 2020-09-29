#pragma once
class SystemDialogs
{
public:
	static std::string OpenFile(const char* _filter);
	static std::string SaveFile(std::string _filter);
};

