#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string.h>
#include <unordered_map>
#include <microhttpd.h>

namespace httpd {

	class HttpRequest {

		private:

			/**
			 * The headers of the request
			 */
			std::unordered_map<std::string, std::string> headers;

			/**
			 * The get arguments of the request
			 */
			std::unordered_map<std::string, std::string> get_args;

			/**
			 * A helper method for looking elements up in a map without creating an entry
			 */
			std::string map_lookup(std::string key, std::unordered_map<std::string, std::string> map);

			bool has_post_data;
			MHD_PostProcessor *post_processor;

		public:

			HttpRequest();
			~HttpRequest();

			//add or get header values
			void add_header(std::string key, std::string value);
			std::string get_header(std::string key);

			//add or get GET args
			void add_ga(std::string key, std::string value);
			std::string get_ga(std::string key);
			
			std::unordered_map<std::string, std::string> get_headers();

			std::unordered_map<std::string, std::string> get_get_args();

			void set_has_post_data(bool has_post_data);
			bool get_has_post_data();

			void set_post_processor(MHD_PostProcessor *post_processor);
			MHD_PostProcessor* get_post_processor();
			
	};

}

#endif
