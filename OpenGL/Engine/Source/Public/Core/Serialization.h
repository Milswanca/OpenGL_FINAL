#pragma once

class Serializer
{
public:
	Serializer();

	void Read(void* _output, size_t _size);
	void Write(void* _data, size_t _size);
	void SaveToFile(const char* _file);

	void Open(const char* _file);
	void Close();

	friend Serializer& operator<<(Serializer& _s, const int& _v);
	friend Serializer& operator>>(Serializer& _s, int& _v);

	friend Serializer& operator<<(Serializer& _s, const size_t& _v);
	friend Serializer& operator>>(Serializer& _s, size_t& _v);

	friend Serializer& operator<<(Serializer& _s, const bool& _v);
	friend Serializer& operator>>(Serializer& _s, bool& _v);

	friend Serializer& operator<<(Serializer& _s, const float& _v);
	friend Serializer& operator>>(Serializer& _s, float& _v);

	friend Serializer& operator<<(Serializer& _s, const char& _v);
	friend Serializer& operator>>(Serializer& _s, char& _v);

	template<typename T>
	friend Serializer& operator<<(Serializer& _s, const std::vector<T>& _v)
	{
		int size = _v.size();
		_s.Write((void*)&size, sizeof(int));
		_s.Write((void*)_v.data(), sizeof(T) * size);

		return _s;
	}

	template<typename T>
	friend Serializer& operator>>(Serializer& _s, std::vector<T>& _v)
	{
		int size;
		_s.Read(&size, sizeof(int));

		_v = std::vector<T>(size);
		_s.Read((void*)&_v[0], sizeof(T) * size);

		return _s;
	}

private:
	size_t m_offset;
	size_t m_totalSize;
	char* m_data;
};