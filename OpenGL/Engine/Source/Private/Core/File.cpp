#include "PCH.h"
#include "File.h"

#include <sstream>

std::string File::LoadFileToString(const char* _file)
{
	std::ifstream is(_file, std::ofstream::binary);
	
	std::string str;
	is.seekg(0, std::ios::end);
	str.reserve(is.tellg());
	is.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(is)),
		std::istreambuf_iterator<char>());

	is.close();
	return str;
}
