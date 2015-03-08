#include "serializer.hpp"

#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <sstream>

#include "../conversion.hpp"

namespace ruuster
{
	void serializer::write(const std::string& key, const bool x)
	{
		write(key, std::string(x ? "true" : "false"));
	}
	
	void serializer::write(const std::string& key, const time_t x)
	{
		write(key, conversion::to_string(x));
	}
	
	void serializer::write(const std::string& key, const date_t x)
	{
		write(key, conversion::to_string(x));
	}
	
	void serializer::write(const std::string& key, const datetime_t x)
	{
		const static std::locale loc(std::locale("en_US.UTF-8"), new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%SZ"));
	
		std::stringstream ss;
		ss.imbue(loc);
		ss << x;
		
		write(key, ss.str());
	}
	
	void serializer::write(const std::string& key, const weekday_t x)
	{
		write(key, conversion::to_string(x));
	}
}
