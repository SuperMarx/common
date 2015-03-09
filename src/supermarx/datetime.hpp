#pragma once

#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_clock.hpp>

namespace supermarx
{
	typedef boost::gregorian::date date;
	typedef boost::posix_time::ptime datetime;

	inline datetime datetime_now()
	{
		return boost::date_time::second_clock<datetime>().local_time();
	}
}
