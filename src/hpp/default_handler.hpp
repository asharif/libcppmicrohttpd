#ifndef DEFAULT_HANDLER_HPP
#define DEFAULT_HANDLER_HPP

#include <http_request_handler.hpp>
#include <log4cpp/Category.hh>

namespace httpd {

	class DefaultHandler : public HttpRequestHandler {

		private:

			static log4cpp::Category &logger;

			void build_response(HttpRequest& request, HttpResponse& response);

		public:

		void handle(HttpRequest& request, HttpResponse& response);

		void handle_streaming_post(HttpRequest& request, HttpResponse& response, std::string filename, std::string content_type,
				 	std::string transfer_encoding, const char *data, uint64_t off, size_t size);


	};

}

#endif
