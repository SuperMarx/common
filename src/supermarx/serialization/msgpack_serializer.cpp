#include "msgpack_serializer.hpp"

namespace supermarx
{

msgpack_serializer::msgpack_serializer()
	: buffer()
	, pk(&buffer)
	, stack()
{}

msgpack_serializer::~msgpack_serializer()
{}

msgpack_serializer::stack_e::stack_e(type_t _t, size_t _n)
	: t(_t)
	, n(_n)
	, i(0)
{}

void msgpack_serializer::write(const std::string& x)
{
	pk.pack_str(x.size());
	pk.pack_str_body(x.data(), x.size());
}

void msgpack_serializer::add_node(const type_t t, const std::string& name, const size_t n)
{
	while(!stack.empty())
	{
		stack_e& s = stack.top();

		if(s.i < s.n)
			break;

		stack.pop();
	}

	if(!stack.empty())
	{
		stack_e& s = stack.top();
		s.i++;

		if(s.t == type_t::map)
			write(name);
	}

	if(t != type_t::non_container && n > 0)
		stack.emplace(t, n);
}

void msgpack_serializer::write_array(const std::string& name, const size_t n)
{
	add_node(type_t::array, name, n);
	pk.pack_array(n);
}

void msgpack_serializer::write_object(const std::string& name, const size_t n)
{
	add_node(type_t::map, name, n);
	pk.pack_map(n);
}

void msgpack_serializer::write(const std::string& key, const uint64_t x)
{
	add_node(type_t::non_container, key, 0);
	pk.pack_uint64(x);
}

void msgpack_serializer::write(const std::string& key, const std::string& x)
{
	add_node(type_t::non_container, key, 0);
	write(x);
}

void msgpack_serializer::write(const std::string& key, const raw& x)
{
	add_node(type_t::non_container, key, 0);
	pk.pack_bin(x.length());
	pk.pack_bin_body(x.data(), x.length());
}

void msgpack_serializer::dump(std::function<void(const char*, size_t)> f)
{
	f(buffer.data(), buffer.size());
}

void msgpack_serializer::clear()
{
	buffer.clear();

	while(!stack.empty())
		stack.pop();
}

}
