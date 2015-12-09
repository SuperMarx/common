#pragma once

#include <supermarx/util/cached_downloader.hpp>
#include <supermarx/util/stubborn.hpp>

#include <functional>
#include <deque>

namespace supermarx
{

class download_manager
{
public:
	typedef std::function<void(downloader::response)> f_t;

	struct job_t
	{
		std::string uri;
		f_t f;

		job_t(job_t const&) = delete;
		job_t(job_t&&) = default;
	};

private:
	cached_downloader& dl;
	std::deque<job_t> queue;

public:
	download_manager(cached_downloader& _dl)
		: dl(_dl)
		, queue()
	{}

	void schedule(std::string&& _uri, f_t&& _f)
	{
		job_t j = {std::move(_uri), std::move(_f)};
		queue.emplace_back(std::move(j));
	}

	void process_all()
	{
		while(!queue.empty())
		{
			job_t j = std::move(queue.front());
			queue.pop_front();

			downloader::response response;
			try
			{
				response = std::move(stubborn::attempt<downloader::response, downloader::error>([&]() {
					return dl.fetch(j.uri);
				}));
			} catch(downloader::error e)
			{
				std::cerr << "Failed " << j.uri << std::endl
					<< '\t' << e.what() << std::endl;
			}

			try
			{
				j.f(response);
			} catch(std::runtime_error e)
			{
				std::cerr << "Failed " << j.uri << std::endl
					<< '\t' << e.what() << std::endl;
			}
		}
	}
};

}
