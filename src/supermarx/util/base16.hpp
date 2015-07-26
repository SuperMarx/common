#pragma once

#include <string>
#include <iomanip>
#include <sstream>

namespace supermarx
{

class base16
{
public:
	template<typename T>
	inline static std::string conv(T const x)
	{
		std::stringstream stream;

		stream << std::setfill ('0')
			   << std::setw(sizeof(T)*2)
			   << std::hex
			   << x;

		return stream.str();
	}
};

}
