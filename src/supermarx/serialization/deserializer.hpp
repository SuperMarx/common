#pragma once

#include <stdexcept>
#include <string>

#include <supermarx/datetime.hpp>
#include <supermarx/raw.hpp>

namespace supermarx
{

class deserializer
{
protected:
	deserializer();

public:
	struct key_error : public std::runtime_error
	{
		key_error(const std::string& expected, const std::string& received);
	};

	struct type_error : public std::runtime_error
	{
		type_error(const std::string& expected, const std::string& received);
	};

	virtual ~deserializer();

	virtual size_t read_array(const std::string& name) = 0;
	virtual size_t read_object(const std::string& name) = 0;

	virtual void read(const std::string& key, uint64_t& x) = 0;
	virtual void read(const std::string& key, std::string& x) = 0;
	virtual void read(const std::string& key, raw& x) = 0;

	void read(const std::string& key, bool& x);
	void read(const std::string& key, time& x);
	void read(const std::string& key, date& x);
	void read(const std::string& key, datetime& x);

	virtual void feed(const std::string& str) = 0;
};

}
