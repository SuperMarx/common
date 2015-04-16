#include <supermarx/serialization/serializer.hpp>

namespace supermarx
{

void serializer::write(const std::string& key, const bool x)
{
	write(key, std::string(x ? "true" : "false"));
}

void serializer::write(const std::string& key, const time x)
{
	write(key, to_string(x));
}

void serializer::write(const std::string& key, const date x)
{
	write(key, to_string(x));
}

void serializer::write(const std::string& key, const datetime x)
{
	write(key, to_string(x));
}

}
