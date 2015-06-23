#pragma once

#include <string>

namespace supermarx
{

enum class measure
{
	UNITS,
	MILLILITERS,
	MILLIGRAMS,
	MILLIMETERS
};

inline std::string to_string(measure m)
{
	switch(m)
	{
	case measure::UNITS:
		return "UNITS";
	case measure::MILLILITERS:
		return "MILLILITERS";
	case measure::MILLIGRAMS:
		return "MILLIGRAMS";
	case measure::MILLIMETERS:
		return "MILLIMETERS";
	}
}

inline measure to_measure(std::string const& str)
{
	if(str == "UNITS")
		return measure::UNITS;
	else if(str == "MILLILITERS")
		return measure::MILLILITERS;
	else if(str == "MILLIGRAMS")
		return measure::MILLIGRAMS;
	else if(str == "MILLIMETERS")
		return measure::MILLIMETERS;

	throw std::runtime_error("Could not parse measure");
}

}
