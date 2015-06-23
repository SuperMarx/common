#pragma once

#include <supermarx/id_t.hpp>

namespace supermarx
{

template<typename T>
class reference
{
private:
	id_t id;

public:
	reference(id_t _id)
	: id(_id)
	{}

	id_t unseal() const // No implicit conversion
	{
		return id;
	}
};

template<typename T>
static inline std::ostream& operator<<(std::ostream& os, reference<T> const& rhs)
{
	os << rhs.unseal();
	return os;
}

}
