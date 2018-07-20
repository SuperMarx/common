#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <yaml-cpp/yaml.h>

#include <supermarx/api/client.hpp>

namespace supermarx
{

template<typename SCRAPER>
class scraper_cli
{
private:
	struct cli_options
	{
		std::string api_host;
		bool cache;
		bool dry_run;
		bool extract_images;
		size_t extract_images_limit;
		bool register_tags;
		size_t ratelimit;
		bool silent;
	};

	static int read_options(cli_options& opt, std::string const& name, std::string const& supermarket_name, int argc, char** argv)
	{
		boost::program_options::options_description o_general("General options");
		o_general.add_options()
				("help,h", "display this message")
				("api,a", boost::program_options::value(&opt.api_host), "api host (default: api.supermarx.nl)")
				("cache,c", "caches assets downloaded from supermarket servers, useful when debugging")
				("dry-run,d", "does not send products to api when set")
				("extract-images,i", "extract product images")
				("extract-images-limit,l", boost::program_options::value(&opt.extract_images_limit), "amount of images allowed to download in one session (default: 60)")
				("register-tags,t", "extract and register tags corresponding to the products")
				("ratelimit,r", boost::program_options::value(&opt.ratelimit), "minimal time between each request in milliseconds (default: 30000)")
				("silent,s", "do not write status reports to cerr");

		boost::program_options::variables_map vm;
		boost::program_options::positional_options_description pos;

		boost::program_options::options_description options("Allowed options");
		options.add(o_general);

		try
		{
			boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options).positional(pos).run(), vm);
		} catch(boost::program_options::unknown_option &e)
		{
			std::cerr << "Unknown option --" << e.get_option_name() << ", see --help." << std::endl;
			return EXIT_FAILURE;
		}

		try
		{
			boost::program_options::notify(vm);
		} catch(const boost::program_options::required_option &e)
		{
			std::cerr << "You forgot this: " << e.what() << std::endl;
			return EXIT_FAILURE;
		}

		if(vm.count("help"))
		{
			std::cout
					<< "SuperMarx scraper for the " << supermarket_name << " inventory. [https://github.com/SuperMarx/" << name << "]" << std::endl
					<< "Usage: ./" << name << " [options]" << std::endl
					<< std::endl
					<< o_general;

			return EXIT_FAILURE;
		}

		if(!vm.count("api"))
			opt.api_host = "https://api.supermarx.nl";

		opt.cache = vm.count("cache");
		opt.dry_run = vm.count("dry-run");
		opt.extract_images = vm.count("extract-images");

		if(!vm.count("extract-images-limit"))
			opt.extract_images_limit = 60;

		opt.register_tags = vm.count("register-tags");

		if(!vm.count("ratelimit"))
			opt.ratelimit = 30000;

		opt.silent = vm.count("silent");

		return EXIT_SUCCESS;
	}

public:
	scraper_cli() = delete;

	static int exec(const id_t supermarket_id, std::string const& name, std::string const& supermarket_name, int argc, char** argv)
	{
		cli_options opt;

		int result = read_options(opt, name, supermarket_name, argc, argv);
		if(result != EXIT_SUCCESS)
			return result;

		supermarx::api::client api(opt.api_host, name + " (libsupermarx-api)");

		char* secret_scraper_username = std::getenv("SECRET_SCRAPER_USERNAME");
		char* secret_scraper_password = std::getenv("SECRET_SCRAPER_PASSWORD");

		if(secret_scraper_username != NULL)
		{
			api.promote(
				std::string(secret_scraper_username),
				std::string(secret_scraper_password)
			);
		}
		else
			std::cerr << "SECRET_SCRAPER_{USERNAME, PASSWORD} not set, assuming debug" << std::endl;

		size_t images_downloaded = 0;
		std::set<std::string> identifiers;
		std::map<message::tag, reference<data::tag>> tag_ids;
		std::map<std::string, std::set<message::tag>> committed_tags;

		auto find_add_tag_f([&](message::tag const& t)
		{
			auto it(tag_ids.find(t));

			if(it == tag_ids.end())
			{
				auto tag_id = api.find_add_tag(t);
				tag_ids.emplace(t, tag_id);
				return tag_id;
			}
			else
				return it->second;
		});

		SCRAPER s([&](
			std::string const& source_uri,
			boost::optional<std::string> const& image_uri_opt,
			message::product_base const& product,
			datetime retrieved_on,
			confidence c,
			std::vector<std::string> problems
		) {
			if(identifiers.emplace(product.identifier).second) // Only commit previously unseen products
			{
				committed_tags.emplace(product.identifier, std::set<message::tag>());

				if(!opt.silent)
				{
					std::cerr << "Product '" << product.name << "' [" << product.identifier << "] ";

					if(product.price == product.orig_price)
						std::cerr << product.price/100.0f << " EUR";
					else
						std::cerr << product.orig_price/100.0f << " EUR -> " << product.price/100.0f << " EUR";

					if(product.discount_amount > 1)
						std::cerr << " (at " << product.discount_amount << ')';

					std::cerr << std::endl;
				}

				if(!opt.dry_run)
				{
					message::add_product ap({product, retrieved_on, c, problems});
					api.add_product(supermarket_id, ap);
				}

				if(opt.extract_images && image_uri_opt)
				{
					bool permission = false;
					if(opt.dry_run)
						permission = true;
					else
					{
						supermarx::message::product_summary ps(api.get_product(supermarket_id, product.identifier));
						if(!ps.imagecitation_id)
							permission = true;
					}

					if(permission && images_downloaded < opt.extract_images_limit)
					{
						supermarx::raw img;

						try
						{
							supermarx::raw img_tmp(s.download_image(*image_uri_opt));
							img.swap(img_tmp);
						} catch(std::runtime_error const& e)
						{
							std::cerr << "Catched error whilst fetching image for " << product.identifier << " " << *image_uri_opt << std::endl;
							std::cerr << e.what() << std::endl;
						}

						if(!opt.dry_run && img.length() > 0)
						{
							try
							{
							api.add_product_image_citation(
								supermarket_id,
								product.identifier,
								*image_uri_opt,
								source_uri,
								datetime_now(),
								std::move(img)
							);
							} catch(std::runtime_error const& e)
							{
								std::cerr << "Catched error whilst pushing image for " << product.identifier << " " << *image_uri_opt << std::endl;
								std::cerr << e.what() << std::endl;
							}
						}

						images_downloaded++;
					}
				}
			}
		},
		[&](message::tag const& parent_tag, message::tag const& child_tag) {
			if(opt.dry_run)
				return;

			if(!opt.register_tags)
				return;

			reference<data::tag> parent_tag_id = find_add_tag_f(parent_tag);
			reference<data::tag> child_tag_id = find_add_tag_f(child_tag);

			api.update_tag_set_parent(child_tag_id, parent_tag_id);
		}, opt.ratelimit, opt.cache, opt.register_tags);

		s.scrape();

		return EXIT_SUCCESS;
	}
};

}

