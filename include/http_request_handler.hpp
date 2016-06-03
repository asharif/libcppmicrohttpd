#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string.h>
#include <http_request.hpp>
#include <http_response.hpp>

namespace httpd {

	class HttpRequestHandler {

		public:

			void virtual handle(HttpRequest& request, HttpResponse& response) = 0;

			void virtual handle_streaming_post(HttpRequest& request, HttpResponse& response, std::string filename, std::string content_type,
				 	std::string transfer_encoding, const char *data, uint64_t off, size_t size) = 0;

	};

}

#endif
