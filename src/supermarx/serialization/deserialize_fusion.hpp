#pragma once

#include <cstddef>
#include <vector>

#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/adapted.hpp>

#include <ruuster-common/serialization/deserializer.hpp>

namespace ruuster
{
	struct deserialize_inconsistency : public std::runtime_error
	{
		deserialize_inconsistency()
		: std::runtime_error("Cannot deserialize: the subject does not conform to the struct definition")
		{}
	};

	template<typename T>
	inline T deserialize(const std::unique_ptr<deserializer>& s, const std::string name);

	namespace detail
	{
		template<typename T, typename N, typename... XS>
		struct deserialize_itr;

		template<typename T>
		struct deserialize_value;

		template<typename T, typename N>
		using name_t = boost::fusion::extension::struct_member_name<T, N::value>;

		template<typename T, typename N>
		using type_t = typename boost::fusion::result_of::value_at<T, N>::type;

		template<typename N>
		using next_t = typename boost::mpl::next<N>::type;

		template<typename T>
		using size_t = typename boost::fusion::result_of::size<T>::type;

		/* Primitives */
		#define deserialize_value_primitive(T)\
		template<> struct deserialize_value<T> { static inline T exec(const std::unique_ptr<deserializer>& s, const std::string& name) { T x; s->read(name, x); return x; } };

		deserialize_value_primitive(id_t)
		deserialize_value_primitive(uint64_t)
		deserialize_value_primitive(std::string)
		deserialize_value_primitive(bool)
		deserialize_value_primitive(time_t)
		deserialize_value_primitive(date_t)
		deserialize_value_primitive(datetime_t)
		deserialize_value_primitive(weekday_t)

		/* Generic case */
		template<typename T>
		struct deserialize_value
		{
			static inline T exec(const std::unique_ptr<deserializer>& s, const std::string& name)
			{
				if(s->read_object(name) != size_t<T>::value)
					throw deserialize_inconsistency();

				return deserialize_itr<T, boost::mpl::int_<0>>::exec(s);
			}
		};

		/* Specialisations */
		template<typename T>
		struct deserialize_value<std::vector<T>>
		{
			static inline std::vector<T> exec(const std::unique_ptr<deserializer>& s, const std::string& name)
			{
				const std::string element_name = name + "_e";
				const std::size_t n = s->read_array(name);

				std::vector<T> xs;
				xs.reserve(n);

				for(std::size_t i = 0; i < n; ++i)
					xs.emplace_back(std::move(deserialize<T>(s, element_name)));

				return xs;
			}
		};

		template<>
		struct deserialize_value<dateperiod_t>
		{
			static inline dateperiod_t exec(const std::unique_ptr<deserializer>& s, const std::string name)
			{
				if(s->read_object(name) != 2)
					throw deserialize_inconsistency();

				date_t first = deserialize_value<date_t>::exec(s, "begin");
				date_t second = deserialize_value<date_t>::exec(s, "end");

				return std::make_pair(std::move(first), std::move(second));
			}
		};

		template<typename T>
		struct deserialize_value<boost::optional<T>>
		{
			static inline boost::optional<T> exec(const std::unique_ptr<deserializer>& s, const std::string name)
			{
				const std::string opt_name = "opt_" + name;
				const std::size_t size = s->read_object(opt_name);

				if(size == 0)
					return boost::none;
				else
					return deserialize_value<T>::exec(s, name);
			}
		};

		/* Mechanics */
		template<typename T, typename N, typename... XS>
		struct deserialize_itr
		{
			static inline T exec(const std::unique_ptr<deserializer>& s, XS&&... xs)
			{
				using current_t = type_t<T, N>;

				current_t x = deserialize_value<current_t>::exec(s, name_t<T, N>::call());
				return deserialize_itr<T, next_t<N>, XS..., current_t>::exec(s, std::forward<XS>(xs)..., std::move(x));
			}
		};

		template<typename T, typename... XS>
		struct deserialize_itr<T, size_t<T>, XS...>
		{
			static inline T exec(const std::unique_ptr<deserializer>&, XS&&... xs)
			{
				return T(std::move(xs)...);
			}
		};
	}

	template<typename T>
	inline T deserialize(const std::unique_ptr<deserializer>& s, const std::string name)
	{
		return detail::deserialize_value<T>::exec(s, name);
	}
}
