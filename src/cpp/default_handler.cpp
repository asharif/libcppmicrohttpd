#include <default_handler.hpp>

log4cpp::Category& httpd::DefaultHandler::logger = log4cpp::Category::getRoot();

void httpd::DefaultHandler::handle(HttpRequest& request, HttpResponse& response) {

	build_response(request, response);
	
	response.write_data(response.get_data_buffer().c_str(), response.get_data_buffer().size(), 200);

}

void httpd::DefaultHandler::handle_streaming_post(HttpRequest& request, HttpResponse& response, std::string filename, std::string content_type,
				 	std::string transfer_encoding, const char *data, uint64_t off, size_t size) {

	logger.debug("inside handle_streaming_post");

	if(off == 0) {

		//if off is 0 then this is the firt call
		build_response(request, response);
		response.add_to_buffer("\n\n POST data:\n");

	} 

	response.add_to_buffer(data);

	if(!size) {

		//if size is 0 this is the last call
		response.write_data(response.get_data_buffer().c_str(), response.get_data_buffer().size(), 200);

	}

}

void httpd::DefaultHandler::build_response(HttpRequest& request, HttpResponse& response) {

	response.add_header("Content-Type", "text/html");

	//lets build a output
	std::string data("libcpphttpd is alive yo! here is what you sent me bro...\n\n");

	data += "headers:\n";

	std::unordered_map<std::string, std::string> headers = request.get_headers();
	std::unordered_map<std::string, std::string> args = request.get_get_args();
	
	for ( auto it = headers.begin(); it != headers.end(); ++it ) {

    data +=  " " + it->first + ":" +  it->second + "\n";

	}

	data += "\nGET args:\n";

	for ( auto it = args.begin(); it != args.end(); ++it ) {

    data +=  " " + it->first + ":" +  it->second + "\n";

	}

	response.add_to_buffer(data);

}

