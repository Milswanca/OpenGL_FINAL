#include "PCH.h"
#include "File.h"

std::string File::LoadFileToString(const char* _file)
{
	std::ifstream t(_file);
	std::string str;

	t.seekg(0, std::ios::end);
	str.reserve((const unsigned int)t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
	std::istreambuf_iterator<char>());

	return str;
}
