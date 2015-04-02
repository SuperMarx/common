#pragma once

#include <boost/optional.hpp>
#include <json/json.h>
#include <stack>

#include <supermarx/serialization/serializer.hpp>

namespace supermarx
{

class json_serializer : public serializer
{
public:
	json_serializer();
	virtual ~json_serializer();

	virtual void write_array(const std::string& name, const size_t n);
	virtual void write_object(const std::string& name, const size_t n);

	virtual void write(const std::string& key, const uint64_t x);
	virtual void write(const std::string& key, const std::string& x);

	virtual void dump(std::function<void(const char*, size_t)> f);
	virtual void clear();

private:
	void add_node(const std::string& name, size_t n, const Json::Value&& node);

	struct stack_e
	{
		Json::Value& node;
		size_t n, i;

		stack_e(Json::Value& _node, size_t _n);
	};

	boost::optional<Json::Value> root;
	std::stack<stack_e> stack;
};

}
