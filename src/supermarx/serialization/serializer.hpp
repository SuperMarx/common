#pragma once

#include <string>
#include <functional>

#include <ruuster-common/id_t.hpp>
#include <ruuster-common/typedefs.hpp>

namespace ruuster
{
	class serializer
	{
	protected:
		serializer() {}
	
	public:
		virtual ~serializer() {}

		virtual void write_array(const std::string& name, const size_t n) = 0;
		virtual void write_object(const std::string& name, const size_t n) = 0;
		
		virtual void write(const std::string& key, const id_t& x) = 0;
		virtual void write(const std::string& key, const uint64_t x) = 0;
		virtual void write(const std::string& key, const std::string& x) = 0;
		
		void write(const std::string& key, const bool x);
		void write(const std::string& key, const time_t x);
		void write(const std::string& key, const date_t x);
		void write(const std::string& key, const datetime_t x);
		void write(const std::string& key, const weekday_t x);

		virtual void dump(std::function<void(const char*, size_t)> f) = 0;
		virtual void clear() = 0;
	};
}
