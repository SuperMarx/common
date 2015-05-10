#pragma once

#include <cassert>
#include <cstring>
#include <memory>
#include <algorithm>

namespace supermarx
{

class raw
{
private:
	std::unique_ptr<char[]> buf;
	size_t len;

public:
	raw()
		: buf()
		, len(0)
	{}

	raw(raw&& rhs)
		: raw()
	{
		swap(rhs);
	}

	raw(size_t _len)
		: buf(new char[_len])
		, len(_len)
	{}

	raw(const char* _src, size_t _len)
		: buf(new char[_len])
		, len(_len)
	{
		std::memcpy(buf.get(), _src, len);
	}

	void swap(raw& rhs)
	{
		std::swap(buf, rhs.buf);
		std::swap(len, rhs.len);
	}

	char* data() const
	{
		return buf.get();
	}

	size_t length() const
	{
		return len;
	}

	char& operator[](size_t i) const
	{
		return buf[i];
	}

	char& get(size_t i) const
	{
		assert(i < len);
		return operator[](i);
	}
};

}
