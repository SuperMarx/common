#include <supermarx/serialization/deserializer.hpp>

#include <boost/regex.hpp>

namespace supermarx
{

deserializer::key_error::key_error(const std::string& expected, const std::string& received)
	: std::runtime_error("Could not deserialize: unexpected key, expected " + expected + ", received " + received)
{}

deserializer::type_error::type_error(const std::string& expected, const std::string& received)
	: std::runtime_error("Could not deserialize: unexpected type, expected " + expected + ", received " + received)
{}

deserializer::deserializer() {}
deserializer::~deserializer() {}

void deserializer::read(const std::string& key, bool& x)
{
	std::string str;
	read(key, str);

	if(str == "true")
		x = true;
	else if(str == "false")
		x = false;
	else
		throw type_error("'true' or 'false'", "x");
}

void deserializer::read(const std::string& key, time& x)
{
	std::string str;
	read(key, str);
	x = to_time(str);
}

void deserializer::read(const std::string& key, date& x)
{
	std::string str;
	read(key, str);
	x = to_date(str);
}

void deserializer::read(const std::string& key, datetime& x)
{
	std::string str;
	read(key, str);
	x = to_datetime(str);
}

}
