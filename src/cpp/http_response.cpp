#include <http_response.hpp>

httpd::HttpResponse::HttpResponse() {

	this->mhd_result = MHD_NO;
}

httpd::HttpResponse::HttpResponse(struct MHD_Connection *connection) {

	this->connection = connection;
	this->mhd_result = MHD_NO;
}

httpd::HttpResponse::~HttpResponse() {

}

void httpd::HttpResponse::add_header(std::string key, std::string value) {

	headers[key] = value;

}


void httpd::HttpResponse::add_to_buffer(std::string data) {

	this->data_buffer += data;

}


std::string httpd::HttpResponse::get_data_buffer() {

	return this->data_buffer;

}

void httpd::HttpResponse::write_data(const char data[], size_t size, uint32_t status_code, bool is_error) {

	struct MHD_Response* mhd_response;
		
	mhd_response = MHD_create_response_from_buffer(size, (void*) data, MHD_RESPMEM_MUST_COPY);
	mhd_result = MHD_queue_response(connection, status_code, mhd_response);
	MHD_destroy_response(mhd_response);

  if(!is_error)
    this->mhd_result = MHD_YES;
  else
    this->mhd_result = MHD_NO;

}

int httpd::HttpResponse::get_mhd_result() {

	return mhd_result;

}
