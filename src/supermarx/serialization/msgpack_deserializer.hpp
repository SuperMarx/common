#pragma once

#include <msgpack.hpp>
#include <stack>

#include <supermarx/serialization/deserializer.hpp>

namespace supermarx
{

class msgpack_deserializer : public deserializer
{
public:
	msgpack_deserializer();
	virtual ~msgpack_deserializer();

	virtual size_t read_array(const std::string& name);
	virtual size_t read_object(const std::string& name);

	virtual void read(const std::string& key, uint64_t& x);
	virtual void read(const std::string& key, std::string& x);
	virtual void read(const std::string& key, raw& x);

	virtual void feed(const std::string& str);

private:
	const msgpack::object& read();
	void read_key(const std::string& key);

private:
	enum type_t
	{
		array,
		map,
		non_container
	};

	struct stack_e
	{
		const msgpack::object* obj_ptr;
		type_t t;
		size_t n, i;

		stack_e(const msgpack::object* obj_ptr, type_t t, size_t n, size_t i);
	};

	msgpack::unpacker pac;
	msgpack::unpacked pac_result;
	std::stack<stack_e> stack;
};

}
