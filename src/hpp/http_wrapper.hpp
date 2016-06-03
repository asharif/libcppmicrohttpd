#ifndef REQUEST_RESPONSE_WRAPPER_HPP
#define REQUEST_RESPONSE_WRAPPER_HPP

#include <http_response.hpp>
#include <http_request.hpp>
#include <http_server.hpp>

namespace httpd {

	class Wrapper {

		private:

			HttpServer *server;
			HttpRequest *request;
			HttpResponse *response;

		public:

			Wrapper(HttpServer* server, HttpRequest* request, HttpResponse* response);
			~Wrapper();

			HttpRequest* get_request();
			HttpResponse* get_response();
			HttpServer* get_server();

	};

}

#endif
