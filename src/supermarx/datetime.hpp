#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/greg_weekday.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

namespace supermarx
{
	typedef boost::posix_time::ptime datetime;

	typedef datetime::time_duration_type time;
	typedef datetime::date_type date;
	typedef boost::date_time::weekdays weekday;

	inline datetime datetime_now()
	{
		return boost::date_time::second_clock<datetime>().local_time();
	}

	inline std::string to_string(const long x, const uint length)
	{
		std::string x_str = boost::lexical_cast<std::string>(x);

		if(x_str.size() >= length)
			return x_str;

		return std::string(length - x_str.size(), '0').append(x_str);
	}

	inline std::ostream& operator<<(std::ostream& os, date const& rhs)
	{
		os << boost::gregorian::to_iso_extended_string(rhs);
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, time const& rhs)
	{
		os << to_string(rhs.hours(), 2) << ':' << to_string(rhs.minutes(), 2) << ':' << to_string(rhs.seconds(), 2);
		return os;
	}

	inline std::ostream& operator<<(std::ostream& os, datetime const& rhs)
	{
		os << rhs.date() << 'T' << rhs.time_of_day();
		return os;
	}

	inline std::string to_string(time const& rhs)
	{
		std::stringstream sstr;
		sstr << rhs;
		return sstr.str();
	}

	inline std::string to_string(date const& rhs)
	{
		std::stringstream sstr;
		sstr << rhs;
		return sstr.str();
	}

	inline std::string to_string(datetime const& rhs)
	{
		std::stringstream sstr;
		sstr << rhs;
		return sstr.str();
	}

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

	inline date next_occurance(size_t month, size_t day)
	{
		date now(datetime_now().date());

		date candidate(now.year(), month, day);
		if(now >= candidate)
			return date(now.year()+1, month, day);
		else
			return candidate;
	}
}
