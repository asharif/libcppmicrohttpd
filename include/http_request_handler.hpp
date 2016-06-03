#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string.h>
#include <http_request.hpp>
#include <http_response.hpp>

namespace httpd {

	/**
	 * All endpoint handlers much inherit and implement the pure virtual functions in this class
	 */
	class HttpRequestHandler {

		public:

			/**
			 * Hanlde requests without any upload data (GET, etc)
			 */
			void virtual handle(HttpRequest& request, HttpResponse& response) = 0;

			/**
			 * Hanlde request with streaming upload data (POST, etc).  This  method will be called over and over 
			 * while there is still data streaming in
			 */
			void virtual handle_streaming_data(HttpRequest& request, HttpResponse& response, std::string filename, std::string content_type,
				 	std::string transfer_encoding, const char *data, uint64_t off, size_t size) = 0;

	};

}

#endif
