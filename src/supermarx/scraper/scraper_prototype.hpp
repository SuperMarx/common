#pragma once

#include <vector>
#include <functional>

#include <supermarx/message/product_base.hpp>
#include <supermarx/message/tag.hpp>

namespace supermarx
{

class scraper_prototype
{
private:
	scraper_prototype() = delete;

public:
	using problems_t = std::vector<std::string>;
	using product_callback_t = std::function<void(const std::string&, boost::optional<std::string> const&, const message::product_base&, datetime, confidence, problems_t)>;
	using tag_hierarchy_callback_t = std::function<void(message::tag const&, message::tag const&)>;
};

}
