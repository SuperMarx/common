#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time/gregorian/formatters.hpp>
#include <boost/date_time/gregorian/greg_weekday.hpp>

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

#include <supermarx/datetime_read.hpp>
#include <supermarx/datetime_write.hpp>
