#pragma once

namespace supermarx
{

namespace detail
{
	template<typename T, size_t LENGTH>
	inline size_t numlength(const T x)
	{
		return std::log10(x)+1;
	}

	template<>
	inline size_t numlength<long, 2>(const long x)
	{
		if(x > 9)
			return 2;
		else
			return 1;
	}

	template<>
	inline size_t numlength<long, 4>(const long x)
	{
		if(x > 999)
			return 4;
		else if(x > 99)
			return 3;
		else if(x > 9)
			return 2;
		else
			return 1;
	}

	template<typename T, size_t LENGTH>
	inline void write_int_to_cstr(char* str, T x)
	{
		size_t x_length(numlength<T, LENGTH>(x));
		int64_t pad_length(LENGTH - x_length);

		for(size_t i = 0; i < pad_length; ++i)
			str[i] = '0';

		for(int64_t i = LENGTH-1; i >= pad_length; --i)
		{
			str[i] = '0' + x % 10;
			x /= 10;
		}
	}

	inline void write_time(char* str, time const& rhs)
	{
		write_int_to_cstr<long, 2>(str, rhs.hours());
		write_int_to_cstr<long, 2>(str+3, rhs.minutes());
		write_int_to_cstr<long, 2>(str+6, rhs.seconds());
	}

	inline void write_date(char* str, date const& rhs)
	{
		auto ymd(rhs.year_month_day());
		write_int_to_cstr<long, 4>(str, ymd.year);
		write_int_to_cstr<long, 2>(str+5, ymd.month);
		write_int_to_cstr<long, 2>(str+8, ymd.day);
	}
}

inline std::string to_string(time const& rhs)
{
	char result[] = "xx:xx:xx";
	detail::write_time(result, rhs);
	return std::string(result);
}

inline std::string to_string(date const& rhs)
{
	char result[] = "xxxx-xx-xx";
	detail::write_date(result, rhs);
	return std::string(result);
}

inline std::string to_string(datetime const& rhs)
{
	char result[] = "xxxx-xx-xxTxx:xx:xx";
	detail::write_date(result, rhs.date());
	detail::write_time(result+11, rhs.time_of_day());
	return std::string(result);
}

inline std::ostream& operator<<(std::ostream& os, time const& rhs)
{
	char result[] = "xx:xx:xx";
	detail::write_time(result, rhs);
	os << result;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, date const& rhs)
{
	char result[] = "xxxx-xx-xx";
	detail::write_date(result, rhs);
	os << result;
	return os;
}

inline std::ostream& operator<<(std::ostream& os, datetime const& rhs)
{
	char result[] = "xxxx-xx-xxTxx:xx:xx";
	detail::write_date(result, rhs.date());
	detail::write_time(result+11, rhs.time_of_day());
	os << result;
	return os;
}

}
