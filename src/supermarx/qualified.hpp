#pragma once

#include <supermarx/reference.hpp>

namespace supermarx
{

template<typename T>
struct qualified
{
	reference<T> id;
	T data;

	qualified(reference<T> _id, T const& _data)
	: id(_id)
	, data(_data)
	{}

	operator T()
	{
		return data;
	}
};

}
