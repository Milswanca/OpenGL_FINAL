#include "PCH.h"
#include "StaticHelpers.h"

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>

void StaticHelpers::ToUTF8(std::string& _str)
{
	int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, _str.c_str(), _str.length(), nullptr, 0);

	std::wstring utf16_str(size, '\0');
	MultiByteToWideChar(CP_ACP, MB_COMPOSITE, _str.c_str(), _str.length(), &utf16_str[0], size);

	int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), nullptr, 0, nullptr, nullptr);
	std::string utf8_str(utf8_size, '\0');
	WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(), utf16_str.length(), &utf8_str[0], utf8_size, nullptr, nullptr);

	_str = utf8_str;
}

void StaticHelpers::CompressString(std::string& _str, int compressionlevel)
{
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	if (deflateInit(&zs, compressionlevel) != Z_OK)
		throw(std::runtime_error("deflateInit failed while compressing."));

	zs.next_in = (Bytef*)_str.data();
	zs.avail_in = _str.size();           // set the z_stream's input

	int ret;
	char outbuffer[32768];
	std::string outstring;

	// retrieve the compressed bytes blockwise
	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = deflate(&zs, Z_FINISH);

		if (outstring.size() < zs.total_out) {
			// append the block to the output string
			outstring.append(outbuffer,
				zs.total_out - outstring.size());
		}
	} while (ret == Z_OK);

	deflateEnd(&zs);

	if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
		std::ostringstream oss;
		oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
		throw(std::runtime_error(oss.str()));
	}

	_str = outstring;
}

void StaticHelpers::DecompressString(std::string& _str)
{
	z_stream zs;                        // z_stream is zlib's control structure
	memset(&zs, 0, sizeof(zs));

	if (inflateInit(&zs) != Z_OK)
		throw(std::runtime_error("inflateInit failed while decompressing."));

	zs.next_in = (Bytef*)_str.data();
	zs.avail_in = _str.size();

	int ret;
	char outbuffer[32768];
	std::string outstring;

	// get the decompressed bytes blockwise using repeated calls to inflate
	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, 0);

		if (outstring.size() < zs.total_out) {
			outstring.append(outbuffer,
				zs.total_out - outstring.size());
		}

	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
		std::ostringstream oss;
		oss << "Exception during zlib decompression: (" << ret << ") "
			<< zs.msg;
		throw(std::runtime_error(oss.str()));
	}

	_str = outstring;
}

void StaticHelpers::CompressData(char*& _data, size_t _size, size_t& _newSize)
{
	unsigned long nCompressedDataSize = _size;
	char* pCompressedData = new char[nCompressedDataSize];

	int nResult = compress2((Bytef*)pCompressedData, &nCompressedDataSize, (const Bytef*)_data, _size, 9);

	if (nResult == Z_OK)
	{
		delete[] _data;
		_data = pCompressedData;
		_newSize = nCompressedDataSize;
	}
}

void StaticHelpers::DecompressData(char*& _data, size_t _originalSize, size_t _compressedSize)
{
	char* pDecompressedData = new char[_originalSize];

	int nResult = uncompress((Bytef*)pDecompressedData, (uLongf*)&_originalSize, (const Bytef*)_data, _compressedSize);

	if (nResult == Z_OK)
	{
		delete[] _data;
		_data = pDecompressedData;
	}
}