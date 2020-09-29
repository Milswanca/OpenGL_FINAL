#include "PCH.h"
#include "Serialization.h"
#include "StaticHelpers.h"

#include <ostream>

Serializer::Serializer()
{
	m_totalSize = 0;
	m_offset = 0;
	m_data = nullptr;
}

void Serializer::Write(void* _data, size_t _size)
{
	char* temp = new char[m_totalSize + _size];
	memcpy(temp, m_data, m_totalSize);

	if (m_data != nullptr)
	{
		delete[] m_data;
	}

	memcpy(temp + m_totalSize, _data, _size);
	m_data = temp;

	m_offset += _size;
	m_totalSize += _size;
}

void Serializer::Read(void* _output, size_t _size)
{
	memcpy(_output, m_data + m_offset, _size);
	m_offset += _size;
}

void Serializer::SaveToFile(const char* _file)
{
	int oldSize = m_totalSize;
	StaticHelpers::CompressData(m_data, m_totalSize, m_totalSize);

	std::ofstream stream(_file, std::ios::binary);
	stream.write((const char*)&oldSize, sizeof(int));
	stream.write((const char*)m_data, m_totalSize);
	stream.close();
}

void Serializer::Open(const char* _file)
{
	std::ifstream stream(_file, std::ios::binary);

	stream.seekg(0, std::ios::end);
	m_totalSize = stream.tellg();
	stream.seekg(0, std::ios::beg);
	
	int size;
	stream.read((char*)&size, sizeof(int));
	m_totalSize -= sizeof(int);

	m_data = new char[m_totalSize];
	stream.read(m_data, m_totalSize);
	stream.close();

	StaticHelpers::DecompressData(m_data, size, m_totalSize);
	m_totalSize = size;
}

void Serializer::Close()
{
	delete[] m_data;
	m_data = nullptr;
}

Serializer& operator<<(Serializer& _s, const int& _v)
{
	_s.Write((void*)&_v, sizeof(int));
	return _s;
}

Serializer& operator>>(Serializer& _s, int& _v)
{
	_s.Read(&_v, sizeof(int));
	return _s;
}

Serializer& operator<<(Serializer& _s, const size_t& _v)
{
	_s.Write((void*)&_v, sizeof(size_t));
	return _s;
}

Serializer& operator>>(Serializer& _s, size_t& _v)
{
	_s.Read(&_v, sizeof(size_t));
	return _s;
}

Serializer& operator<<(Serializer& _s, const bool& _v)
{
	_s.Write((void*)&_v, sizeof(bool));
	return _s;
}

Serializer& operator>>(Serializer& _s, bool& _v)
{
	_s.Read(&_v, sizeof(bool));
	return _s;
}

Serializer& operator<<(Serializer& _s, const float& _v)
{
	_s.Write((void*)&_v, sizeof(float));
	return _s;
}

Serializer& operator>>(Serializer& _s, float& _v)
{
	_s.Read(&_v, sizeof(float));
	return _s;
}

Serializer& operator<<(Serializer& _s, const char& _v)
{
	_s.Write((void*)&_v, sizeof(char));
	return _s;
}

Serializer& operator>>(Serializer& _s, char& _v)
{
	_s.Read(&_v, sizeof(char));
	return _s;
}