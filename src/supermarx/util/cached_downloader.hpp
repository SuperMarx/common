#pragma once

#include <fstream>

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>

#include <supermarx/util/downloader.hpp>
#include <supermarx/util/base16.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/crc.hpp>

namespace supermarx
{

class cached_downloader
{
	downloader dl;
	boost::optional<std::string> cache_path;

	std::string mangle_url(std::string const& url)
	{
		static constexpr size_t max_length = 128;

		std::string result = url;

		for(char c : {'/', ':', '?', ','})
			std::replace(result.begin(), result.end(), c, '-');

		if(result.size() > max_length)
		{
			boost::crc_32_type crc;
			crc.process_bytes(url.c_str(), url.size());
			result.erase(result.begin()+max_length-9, result.end());
			result += "-" + base16::conv<uint32_t>(crc.checksum());
		}

		return result;
	}

public:
	cached_downloader(const std::string& agent, unsigned int ratelimit = 0, boost::optional<std::string> _cache_path = boost::none)
		: dl(agent, ratelimit)
		, cache_path(_cache_path)
	{}

	downloader::response fetch(std::string const& url)
	{
		std::string mangled_url = mangle_url(url);

		if(!cache_path)
			return dl.fetch(url);

		boost::filesystem::path p(*cache_path);
		if(!boost::filesystem::is_directory(p))
			throw std::runtime_error("Cache path does not exist");

		p /= mangled_url;
		if(boost::filesystem::exists(p))
		{
			std::ifstream fin(p.generic_string(), std::ios::binary);
			return {200, std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>())};
		}

		downloader::response response(dl.fetch(url));

		if(response.code != 200)
			throw downloader::error(std::string("Received HTTP code ") + boost::lexical_cast<std::string>(response.code));

		std::ofstream fout(p.generic_string(), std::ios::binary);
		fout << response.body;

		return {200, response.body}; // HTTP OK
	}
};

}
