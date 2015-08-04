#pragma once

#include <string>

namespace supermarx
{

enum class measure
{
	UNITS,
	MILLILITRES,
	MILLIGRAMS,
	MILLIMETRES
};

inline std::string to_string(measure m)
{
	switch(m)
	{
	case measure::UNITS:
		return "UNITS";
	case measure::MILLILITRES:
		return "MILLILITRES";
	case measure::MILLIGRAMS:
		return "MILLIGRAMS";
	case measure::MILLIMETRES:
		return "MILLIMETRES";
	}
}

inline measure to_measure(std::string const& str)
{
	if(str == "UNITS")
		return measure::UNITS;
	else if(str == "MILLILITRES")
		return measure::MILLILITRES;
	else if(str == "MILLIGRAMS")
		return measure::MILLIGRAMS;
	else if(str == "MILLIMETRES")
		return measure::MILLIMETRES;

	throw std::runtime_error("Could not parse measure");
}

}
