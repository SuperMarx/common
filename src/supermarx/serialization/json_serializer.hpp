#pragma once

#include <supermarx/serialization/serializer.hpp>

#define RAPIDJSON_HAS_STDSTRING 1

#include <rapidjson/rapidjson.h>
#include <rapidjson/writer.h>
#include <rapidjson/memorybuffer.h>

#undef RAPIDJSON_HAS_STDSTRING

#include <boost/optional.hpp>
#include <stack>

namespace supermarx
{

class json_serializer : public serializer
{
public:
	json_serializer();
	virtual ~json_serializer();

	virtual void write_array(const std::string& name, const size_t n);
	virtual void write_object(const std::string& name, const size_t n);
	virtual void write_null(const std::string& name);

	virtual void write(const std::string& key, const uint64_t x);
	virtual void write(const std::string& key, const std::string& x);
	virtual void write(const std::string& key, const raw& x);
	virtual void write(const std::string& key, const token& x);

	virtual void dump(std::function<void(const char*, size_t)> f);
	virtual void clear();

private:
	enum type_t
	{
		array,
		map,
		non_container
	};

	struct stack_e
	{
		type_t t;
		size_t n, i;

		stack_e(type_t t, size_t n);
	};

	void add_node(const type_t t, const std::string& name, const size_t n);

	rapidjson::MemoryBuffer sb;
	rapidjson::Writer<decltype(sb)> w;

	std::stack<stack_e> stack;
};

}
