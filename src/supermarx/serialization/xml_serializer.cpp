#include <supermarx/serialization/xml_serializer.hpp>

#include <boost/lexical_cast.hpp>
#include <limits>
#include <stdexcept>

namespace supermarx
{

xml_serializer::xml_serializer()
	: doc()
	, stack()
{
	stack.emplace(&doc, std::numeric_limits<size_t>::max());
}

xml_serializer::~xml_serializer()
{}

xml_serializer::stack_e::stack_e(tinyxml2::XMLNode *_node, size_t _n)
	: node(_node)
	, n(_n)
	, i(0)
{}

void xml_serializer::add_node(tinyxml2::XMLNode* n)
{
	while(!stack.empty())
	{
		stack_e& s = stack.top();
		if(s.i < s.n)
		{
			s.node->InsertEndChild(n);
			s.i++;
			return;
		}

		stack.pop();
	}

	throw std::logic_error("Stack may never be empty");
}

void xml_serializer::write_array(const std::string& name, const size_t n)
{
	tinyxml2::XMLNode *node = doc.NewElement(name.c_str());
	add_node(node);
	stack.emplace(node, n);
}

void xml_serializer::write_object(const std::string& name, const size_t n)
{
	write_array(name, n); //Identical
}

void xml_serializer::write(const std::string& key, const uint64_t x)
{
	write(key, boost::lexical_cast<std::string>(x));
}

void xml_serializer::write(const std::string& key, const std::string& x)
{
	tinyxml2::XMLNode *node = doc.NewElement(key.c_str());
	node->InsertEndChild(doc.NewText(x.c_str()));
	add_node(node);
}

void xml_serializer::dump(std::function<void(const char*, size_t)> f)
{
	tinyxml2::XMLPrinter printer;
	doc.Print(&printer);

	const char* data = printer.CStr();
	f(data, std::strlen(data));
}

void xml_serializer::clear()
{
	doc.DeleteChildren();

	while(stack.size() > 1)
		stack.pop();
}

}
