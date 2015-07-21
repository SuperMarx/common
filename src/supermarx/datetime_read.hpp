#pragma once

#include <string>
#include <boost/regex.hpp>

#include <supermarx/datetime.hpp>

namespace supermarx
{

namespace detail
{
	template<typename T, size_t LENGTH>
	inline T read_num_from_cstr(char const* str)
	{
		T result(0);

		for(size_t i = 0; i < LENGTH; ++i)
		{
			const T digit = str[i] - '0';
			if(digit < 0 || digit > 9)
				throw std::runtime_error("Invalid digit in number string");

			result *= 10;
			result += digit;
		}

		return result;
	}

	inline time to_time_long(char const* str_ptr)
	{
		// Expect xx:xx:xx
		auto check([](char reality, char expected)
		{
			if(reality != expected)
				throw std::runtime_error("Time string not in valid format");
		});

		check(str_ptr[2], ':');
		check(str_ptr[5], ':');

		return time(
			read_num_from_cstr<long, 2>(str_ptr+0),
			read_num_from_cstr<long, 2>(str_ptr+3),
			read_num_from_cstr<long, 2>(str_ptr+6)
		);
	}

	inline time to_time_short(char const* str_ptr)
	{
		// Expect xx:xx
		auto check([](char reality, char expected)
		{
			if(reality != expected)
				throw std::runtime_error("Time string not in valid format");
		});

		check(str_ptr[2], ':');

		return time(
			read_num_from_cstr<long, 2>(str_ptr+0),
			read_num_from_cstr<long, 2>(str_ptr+3),
			0
		);
	}

	inline date to_date(char const* str_ptr)
	{
		// Expect xxxx-xx-xx
		auto check([](char reality, char expected)
		{
			if(reality != expected)
				throw std::runtime_error("Date string not in valid format");
		});

		check(str_ptr[4], '-');
		check(str_ptr[7], '-');

		return date(
			read_num_from_cstr<long, 4>(str_ptr+0),
			read_num_from_cstr<long, 2>(str_ptr+5),
			read_num_from_cstr<long, 2>(str_ptr+8)
		);
	}

	inline datetime to_datetime(char const* str_ptr)
	{
		if(str_ptr[10] != ' ' && str_ptr[10] != 'T')
			throw std::runtime_error("Datetime string not in valid format (xxxx-xx-xxTxx:xx:xx)");

		return datetime(
			to_date(str_ptr+0),
			to_time_long(str_ptr+11)
		);
	}
}

inline time to_time(std::string const& str)
{
	if(str.size() == 8)
		return detail::to_time_long(str.c_str());
	else if(str.size() == 6)
		return detail::to_time_short(str.c_str());
	else
		throw std::runtime_error("Time string not in valid format (xx:xx:xx or xx:xx)");
}

inline date to_date(std::string const& str)
{
	if(str.size() == 10)
		return detail::to_date(str.c_str());
	else
		throw std::runtime_error("Date string not in valid format (xxxx-xx-xx)");
}

inline datetime to_datetime(std::string const& str)
{
	if(str.size() == 19)
		return detail::to_datetime(str.c_str());
	else
		throw std::runtime_error("Datetime string not in valid format (xxxx-xx-xxTxx:xx:xx)");
}

}
