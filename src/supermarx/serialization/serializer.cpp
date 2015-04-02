#include <supermarx/serialization/serializer.hpp>

#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <sstream>

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
	const static std::locale loc(std::locale("en_US.UTF-8"), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%SZ"));

	std::stringstream ss;
	ss.imbue(loc);
	ss << x;

	write(key, ss.str());
}

}
