#pragma once

#include <msgpack.hpp>
#include <stack>

#include <supermarx/serialization/serializer.hpp>

namespace supermarx
{

class msgpack_serializer : public serializer
{
public:
	msgpack_serializer();
	virtual ~msgpack_serializer();
	
public:
	virtual void write_array(const std::string& name, const size_t n);
	virtual void write_object(const std::string& name, const size_t n);

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
	void write(const std::string& x);

	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk;
	std::stack<stack_e> stack;
};

}
