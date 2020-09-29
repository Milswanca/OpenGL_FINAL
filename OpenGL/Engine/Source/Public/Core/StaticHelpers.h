#pragma once
#include <zlib.h>

class StaticHelpers
{
public:
	static void ToUTF8(std::string& _str);

	static void CompressString(std::string& _str, int compressionlevel = Z_BEST_COMPRESSION);
	static void DecompressString(std::string& _str);

	static void CompressData(char*& _data, size_t _size, size_t& _newSize);
	static void DecompressData(char*& _data, size_t _originalSize, size_t _compressedSize);
};

