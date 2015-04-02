#include <supermarx/serialization/msgpack_deserializer.hpp>

#include <cstring>

namespace supermarx
{

msgpack_deserializer::msgpack_deserializer()
	: pac()
	, pac_result()
	, stack()
{}

msgpack_deserializer::~msgpack_deserializer()
{}

msgpack_deserializer::stack_e::stack_e(const msgpack::object* _obj_ptr, type_t _t, size_t _n, size_t _i)
	: obj_ptr(_obj_ptr)
	, t(_t)
	, n(_n)
	, i(_i)
{}

void msgpack_deserializer::feed(const std::string& str)
{
	pac.reserve_buffer(str.size());
	memcpy(pac.buffer(), str.data(), str.size());
	pac.buffer_consumed(str.size());
}

const msgpack::object& msgpack_deserializer::read()
{
	if(stack.empty())
	{
		if(!pac.next(&pac_result))
			throw type_error("anything", "nothing (stream empty)");

		stack.emplace(&pac_result.get(), type_t::non_container, 1, 0);
	}

	stack_e& e = stack.top();
	const msgpack::object* result_ptr;

	switch(e.t)
	{
	case type_t::array:
		result_ptr = &e.obj_ptr->via.array.ptr[e.i];
		break;
	case type_t::map:
	{
		msgpack::object_kv& kv = e.obj_ptr->via.map.ptr[e.i/2];
		result_ptr = (e.i % 2 == 0) ? &kv.key : &kv.val;
	}
		break;
	case type_t::non_container:
		result_ptr = e.obj_ptr;
		break;
	}

	e.i++;

	if(e.i >= e.n)
		stack.pop();

	return *result_ptr;
}

std::string convert_msgpack_type(const msgpack::type::object_type t)
{
	switch(t)
	{
	case msgpack::type::ARRAY:
		return "ARRAY";
	case msgpack::type::BOOLEAN:
		return "BOOLEAN";
	case msgpack::type::FLOAT:
		return "FLOAT";
	case msgpack::type::MAP:
		return "MAP";
	case msgpack::type::NEGATIVE_INTEGER:
		return "NEGATIVE_INTEGER";
	case msgpack::type::NIL:
		return "NIL";
	case msgpack::type::POSITIVE_INTEGER:
		return "POSITIVE_INTEGER";
	case msgpack::type::STR:
		return "STR";
	case msgpack::type::BIN:
		return "BIN";
	case msgpack::type::EXT:
		return "EXT";
	default:
		return "UNKNOWN";
	}
}

void msgpack_deserializer::read_key(const std::string& key)
{
	if(stack.empty() || stack.top().t != type_t::map)
		return; //Do not check if we're not in a map

	const msgpack::object& obj = read();
	if(obj.type != msgpack::type::STR)
		throw type_error(convert_msgpack_type(msgpack::type::STR), convert_msgpack_type(obj.type));

	const std::string received(obj.via.str.ptr, obj.via.str.size);
	if(key != received)
		throw key_error(key, received);
}

size_t msgpack_deserializer::read_array(const std::string& name)
{
	read_key(name);

	const msgpack::object& obj = read();
	if(obj.type != msgpack::type::ARRAY)
		throw type_error(convert_msgpack_type(msgpack::type::ARRAY), convert_msgpack_type(obj.type));

	if(obj.via.array.size > 0)
		stack.emplace(&obj, type_t::array, obj.via.array.size, 0);

	return obj.via.array.size;
}

size_t msgpack_deserializer::read_object(const std::string& name)
{
	read_key(name);

	const msgpack::object& obj = read();
	if(obj.type != msgpack::type::MAP)
		throw type_error(convert_msgpack_type(msgpack::type::MAP), convert_msgpack_type(obj.type));

	if(obj.via.map.size > 0)
		stack.emplace(&obj, type_t::map, obj.via.map.size*2, 0);

	return obj.via.map.size;
}

void msgpack_deserializer::read(const std::string& key, uint64_t& x)
{
	read_key(key);

	const msgpack::object& obj = read();
	if(obj.type != msgpack::type::POSITIVE_INTEGER)
		throw type_error(convert_msgpack_type(msgpack::type::POSITIVE_INTEGER), convert_msgpack_type(obj.type));

	x = obj.via.u64;
}

void msgpack_deserializer::read(const std::string& key, std::string& x)
{
	read_key(key);

	const msgpack::object& obj = read();
	if(obj.type != msgpack::type::STR)
		throw type_error(convert_msgpack_type(msgpack::type::STR), convert_msgpack_type(obj.type));

	x = std::string(obj.via.str.ptr, obj.via.str.size);
}

}
