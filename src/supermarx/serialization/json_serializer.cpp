#include "json_serializer.hpp"

#include <stdexcept>

namespace ruuster
{
	json_serializer::json_serializer()
	: stack()
	{}

	json_serializer::~json_serializer()
	{}

	json_serializer::stack_e::stack_e(Json::Value& node, size_t n)
	: node(node)
	, n(n)
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

	void json_serializer::write(const std::string& key, const id_t& x)
	{
		write(key, x.to_hexstr());
	}
	
	void json_serializer::write(const std::string& key, const uint64_t x)
	{
		add_node(key, 0, Json::Value((Json::UInt64) x));
	}

	void json_serializer::write(const std::string& key, const std::string& x)
	{
		add_node(key, 0, Json::Value(x));
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
