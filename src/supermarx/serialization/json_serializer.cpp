#include <supermarx/serialization/json_serializer.hpp>

#include <stdexcept>

#include <supermarx/util/base64.hpp>

namespace supermarx
{

json_serializer::json_serializer()
	: sb()
	, w(sb)
	, stack()
{}

json_serializer::~json_serializer()
{}

json_serializer::stack_e::stack_e(type_t _t, size_t _n)
	: t(_t)
	, n(_n)
	, i(0)
{}

void json_serializer::add_node(const type_t t, const std::string& name, const size_t n)
{
	while(!stack.empty())
	{
		stack_e& s = stack.top();

		if(s.i < s.n)
			break;

		if(s.t == type_t::array)
			w.EndArray();
		else if(s.t == type_t::map)
			w.EndObject();

		stack.pop();
	}

	if(!stack.empty())
	{
		stack_e& s = stack.top();
		s.i++;

		if(s.t == type_t::map)
			w.String(name);
	}

	if(t != type_t::non_container && n > 0)
		stack.emplace(t, n);

	if(t == type_t::array)
		w.StartArray();
	else if(t == type_t::map)
		w.StartObject();
}

void json_serializer::write_array(const std::string& name, const size_t n)
{
	add_node(type_t::array, name, n);
}

void json_serializer::write_object(const std::string& name, const size_t n)
{
	add_node(type_t::map, name, n);
}

void json_serializer::write_null(const std::string& name)
{
	add_node(type_t::non_container, name, 0);
	w.Null();
}

void json_serializer::write(const std::string& key, const uint64_t x)
{
	add_node(type_t::non_container, key, 0);
	w.Uint64(x);
}

void json_serializer::write(const std::string& key, const std::string& x)
{
	add_node(type_t::non_container, key, 0);
	w.String(x);
}

void json_serializer::write(const std::string& key, const raw& x)
{
	add_node(type_t::non_container, key, 0);
	w.String(base64::conv(x.data(), x.length()));
}

void json_serializer::write(const std::string &key, const token &x)
{
	write(key, to_string(x));
}

void json_serializer::dump(std::function<void(const char*, size_t)> f)
{
	while(!stack.empty())
	{
		stack_e& s = stack.top();

		if(s.i != s.n)
			throw std::runtime_error("Did not finish constructing objects before dumping");

		if(s.t == type_t::array)
			w.EndArray();
		else if(s.t == type_t::map)
			w.EndObject();

		stack.pop();
	}

	f(sb.GetBuffer(), sb.GetSize());
}

void json_serializer::clear()
{
	sb.Clear();
	w.Reset(sb);

	while(!stack.empty())
		stack.pop();
}

}
