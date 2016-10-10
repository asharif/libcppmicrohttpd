#ifndef DEFAULT_HANDLER_HPP
#define DEFAULT_HANDLER_HPP

#include <http_request_handler.hpp>

namespace httpd {

	class DefaultHandler : public HttpRequestHandler {

		private:

			void build_response(HttpRequest& request, HttpResponse& response);

		public:

		void handle(HttpRequest& request, HttpResponse& response);

		void handle_streaming_data(HttpRequest& request, HttpResponse& response, std::string filename, std::string content_type,
				 	std::string transfer_encoding, const char *data, uint64_t off, size_t size);


	};

}

#endif
