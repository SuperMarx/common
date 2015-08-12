#include <supermarx/serialization/json_serializer.hpp>

#include <stdexcept>

#include <supermarx/util/base64.hpp>

namespace supermarx
{

json_serializer::json_serializer()
	: stack()
{}

json_serializer::~json_serializer()
{}

json_serializer::stack_e::stack_e(Json::Value& _node, size_t _n)
	: node(_node)
	, n(_n)
	, i(0)
{}

void json_serializer::add_node(const std::string& name, size_t n, const Json::Value&& node)
{
	while(!stack.empty())
	{
		stack_e& s = stack.top();

		if(s.i < s.n)
			break;

		stack.pop();
	}

	if(stack.empty())
	{
		if(root)
			throw std::logic_error("Setting root twice");

		root = node;
		stack.emplace(root.get(), n);
	}
	else
	{
		stack_e& s = stack.top();
		s.i++;

		if(s.node.isArray())
			stack.emplace(s.node.append(node), n);
		else if(s.node.isObject())
			stack.emplace(s.node[name] = node, n);
	}
}

void json_serializer::write_array(const std::string& name, const size_t n)
{
	add_node(name, n, Json::Value(Json::arrayValue));
}

void json_serializer::write_object(const std::string& name, const size_t n)
{
	add_node(name, n, Json::Value(Json::objectValue));
}

void json_serializer::write_null(const std::string& name)
{
	add_node(name, 0, Json::nullValue);
}

void json_serializer::write(const std::string& key, const uint64_t x)
{
	add_node(key, 0, Json::Value(static_cast<Json::UInt64>(x)));
}

void json_serializer::write(const std::string& key, const std::string& x)
{
	add_node(key, 0, Json::Value(x));
}

void json_serializer::write(const std::string& key, const raw& x)
{
	write(key, base64::conv(x.data(), x.length()));
}

void json_serializer::write(const std::string &key, const token &x)
{
	write(key, to_string(x));
}

void json_serializer::dump(std::function<void(const char*, size_t)> f)
{
	Json::StyledWriter w;
	std::string result;

	if(root)
		result = w.write(root.get());

	f(result.data(), result.size());
}

void json_serializer::clear()
{
	root.reset();

	while(!stack.empty())
		stack.pop();
}

}
