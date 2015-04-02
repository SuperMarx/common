#pragma once

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/struct.hpp>

#include <supermarx/serialization/serializer.hpp>

#include <boost/optional.hpp>

namespace supermarx
{
namespace detail
{

template<typename T, typename N>
struct serialize_itr;

template<typename T>
struct serialize_value;

/* Primitives */
#define serialize_value_primitive(T)\
	template<> struct serialize_value<T> { static inline void exec(const std::unique_ptr<serializer>& s, const std::string name, const T& x) { s->write(name, x); } };

serialize_value_primitive(uint64_t)
serialize_value_primitive(std::string)
serialize_value_primitive(bool)
serialize_value_primitive(time)
serialize_value_primitive(date)
serialize_value_primitive(datetime)

/* Generic case */
template<typename T>
struct serialize_value
{
	static inline void exec(const std::unique_ptr<serializer>& s, const std::string name, const T& x)
	{
		s->write_object(name, boost::fusion::result_of::size<T>::value);
		detail::serialize_itr<T, boost::mpl::int_<0>>::exec(s, x);
	}
};

/* Specializations */
template<typename T>
struct serialize_value<std::vector<T>>
{
	static inline void exec(const std::unique_ptr<serializer>& s, const std::string name, const std::vector<T>& xs)
	{
		const std::string element_name = name + "_e";
		s->write_array(name, xs.size());
		for(const T& x : xs)
			serialize_value<T>::exec(s, element_name, x);
	}
};

template<typename T>
struct serialize_value<boost::optional<T>>
{
	static inline void exec(const std::unique_ptr<serializer>& s, const std::string name, const boost::optional<T>& x)
	{
		const std::string opt_name = "opt_" + name;

		if(x)
		{
			s->write_object(opt_name, 1);
			serialize_value<T>::exec(s, name, x.get());
		}
		else
			s->write_object(opt_name, 0);
	}
};

template<>
struct serialize_value<condition>
{
	static inline void exec(const std::unique_ptr<serializer>& s, const std::string name, const condition& xs)
	{
		s->write(name, to_string(xs));
	}
};

template<typename T, typename N>
using name_t = boost::fusion::extension::struct_member_name<T, N::value>;

template<typename T, typename N>
using type_t = typename boost::fusion::result_of::value_at<T, N>::type;

template<typename N>
using next_t = typename boost::mpl::next<N>::type;

template<typename T>
using size_t = typename boost::fusion::result_of::size<T>::type;

template<typename T, typename N>
struct serialize_itr
{
	static inline void exec(const std::unique_ptr<serializer>& s, const T& x)
	{
		using current_t = type_t<T, N>;
		serialize_value<current_t>::exec(s, name_t<T, N>::call(), boost::fusion::at<N>(x));
		serialize_itr<T, next_t<N>>::exec(s, x);
	}
};

template<typename T>
struct serialize_itr<T, size_t<T>>
{
	static inline void exec(const std::unique_ptr<serializer>&, const T&) {}
};

} // Back to namespace supermarx

template<typename T>
void inline serialize(const std::unique_ptr<serializer>& s, const std::string name, const T& x)
{
	detail::serialize_value<T>::exec(s, name, x);
}

}
