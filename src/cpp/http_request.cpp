#include <http_request.hpp>

httpd::HttpRequest::HttpRequest() {

	has_post_data = false;

}

httpd::HttpRequest::~HttpRequest() {

}


//add or get GET or HEADER args
void httpd::HttpRequest::add_arg(std::string key, std::string value) {

	get_args[key] = value;

}

std::string httpd::HttpRequest::get_arg(std::string key) {

	return map_lookup(key, get_args);

}

std::string httpd::HttpRequest::map_lookup(std::string key, std::unordered_map<std::string, std::string> map) {

	std::string result("");
	std::unordered_map<std::string, std::string>::const_iterator got = map.find(key);
	
	if( got != map.end()) {

		//if the key exists then lets set it as a response
		result = map[key];

	}

	return result;

}

std::unordered_map<std::string, std::string> httpd::HttpRequest::get_get_args() {

	return this->get_args;

}

void httpd::HttpRequest::set_has_post_data(bool has_post_data){

	this->has_post_data = has_post_data;

}

bool httpd::HttpRequest::get_has_post_data(){

	return this->has_post_data;

}

void httpd::HttpRequest::set_post_processor(MHD_PostProcessor *post_processor){

	this->post_processor = post_processor;

}

MHD_PostProcessor* httpd::HttpRequest::get_post_processor(){

	return this->post_processor;

}

void httpd::HttpRequest::set_prop(std::string key, void* value) {

  this->props[key] = value;

}

void* httpd::HttpRequest::get_prop(std::string key) {

  void *result = NULL;

  std::unordered_map<std::string, void*>::const_iterator got = this->props.find(key);

	if( got != this->props.end()) {

    result = this->props[key];
  }

  return result;

}




