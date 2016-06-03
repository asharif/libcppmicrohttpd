#include <http_wrapper.hpp>

httpd::Wrapper::Wrapper(HttpServer* server, HttpRequest* request, HttpResponse* response) {

	this->server = server;
	this->request = request;
	this->response = response;

}


httpd::Wrapper::~Wrapper() {

	delete this->request;
	delete this->response;

}

httpd::HttpServer* httpd::Wrapper::get_server() {

	return this->server;

}

httpd::HttpRequest* httpd::Wrapper::get_request() {

	return this->request;
}

httpd::HttpResponse* httpd::Wrapper::get_response() {

	return this->response;

}

