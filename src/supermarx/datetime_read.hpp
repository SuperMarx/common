#pragma once

#include <string>
#include <boost/regex.hpp>

#include <supermarx/datetime.hpp>

namespace supermarx
{

inline time to_time(std::string const& str)
{
	const static boost::regex full_regex("([0-9]{2}):([0-9]{2}):([0-9]{2})");
	const static boost::regex short_regex("([0-9]{2}):([0-9]{2})");

	boost::smatch match;
	if(boost::regex_match(str, match, full_regex))
		return time(
			std::stol(match[1]),
			std::stol(match[2]),
			std::stol(match[3])
		);
	else if(boost::regex_match(str, match, short_regex))
		return time(
			std::stol(match[1]),
			std::stol(match[2]),
			0
		);

	throw std::runtime_error("Can not parse time-string");
}

inline date to_date(std::string const& str)
{
	const static boost::regex int_regex("([0-9]{4})-([0-9]{2})-([0-9]{2})");

	boost::smatch match;
	if(boost::regex_match(str, match, int_regex))
		return date(
			std::stoul(match[1]),
			std::stoul(match[2]),
			std::stoul(match[3])
		);

	throw std::runtime_error("Can not parse date-string");
}

inline datetime to_datetime(std::string const& str)
{
	const static boost::regex int_regex("([0-9]{4})-([0-9]{2})-([0-9]{2})[T| ]([0-9]{2}):([0-9]{2}):([0-9]{2})");
	boost::smatch match;
	if(boost::regex_match(str, match, int_regex))
		return datetime(
			date(
				std::stoul(match[1]),
				std::stoul(match[2]),
				std::stoul(match[3])
			),
			time(
				std::stol(match[4]),
				std::stol(match[5]),
				std::stol(match[6])
			)
		);

	throw std::runtime_error("Can not parse datetime-string");
}

}
