#include <http_server.hpp>
#include <chrono>
#include <thread>
#include <http_wrapper.hpp>

log4cpp::Category& httpd::HttpServer::logger = log4cpp::Category::getRoot();

httpd::HttpServer::HttpServer(uint32_t port, uint32_t tpool_size) {

	this->port = port;
	this->tpool_size = tpool_size;

}

httpd::HttpServer::~HttpServer(){


}

void httpd::HttpServer::start() {

	using namespace std;

	mhd_daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, port, NULL, NULL, &front_controller_c_hook, this,
			MHD_OPTION_THREAD_POOL_SIZE, tpool_size, MHD_OPTION_END);

	if(mhd_daemon == NULL) {

		cout << "Could not init the http server!" << endl;
		exit(1);

	}

	stringstream port_msg;
	port_msg	<< "HttpServer running on port: " <<  port << " with a threadpool size of: " << tpool_size;
	logger.info(port_msg.str());

	while(true) {

		//lets block until kill signal of some sort
		std::this_thread::sleep_for(std::chrono::milliseconds(60000));

	}

}

int httpd::HttpServer::front_controller_c_hook(void* registered_arg, struct MHD_Connection *connection, const char *url,
		const char *method, const char *version, const char *upload_data,
		size_t *upload_data_size, void **ptr) {

	//cast the pointer to a http server
	HttpServer* server = (HttpServer*)registered_arg;

	int result;

	if (*ptr == NULL) {

		//The first time only the headers are valid, lets build a new request, read the headers and the get arguments into it
		HttpRequest* request = new HttpRequest();
		MHD_get_connection_values(connection, (MHD_ValueKind(MHD_HEADER_KIND | MHD_GET_ARGUMENT_KIND)), &HttpServer::request_header_builder, request);
		std::string cpp_url(url);
		//lets also add request url
		request->add_header("req_url", cpp_url);

		//build a http response
		HttpResponse* response = new HttpResponse(connection);

		//now lets wrap the server, response and request for this instance
		Wrapper* wrapper = new Wrapper(server, request, response);

		//create our post processor
		MHD_PostProcessor* post_processor = MHD_create_post_processor(connection, 1024, &httpd::HttpServer::post_processor, wrapper);
		request->set_post_processor(post_processor);

		//lets put the wrapper into ptr so it gets passed back to us each time this is called
		*ptr = wrapper;

		result = MHD_YES;

	} else if(*upload_data_size) {


		//the ptr is our state machine friend yo!
		Wrapper* wrapper = (httpd::Wrapper*)(*ptr);

		if(!wrapper->get_request()->get_has_post_data()) {

			//if we haven't set this yet then set it
			wrapper->get_request()->set_has_post_data(true);

		}

		//process post

		MHD_PostProcessor* post_processor = wrapper->get_request()->get_post_processor();
		int process_result = MHD_post_process(post_processor, upload_data, *upload_data_size);
		if(process_result == MHD_NO) {

			logger.error("there was an issue processing post data yo!");
		}

		if(*upload_data_size > 1024) {

			*upload_data_size -= 1024 ;

		} else {

			*upload_data_size = 0;

		};

		result = MHD_YES;

	} else {

		//we either don't have any post data or are finished dealing with the post data.
		//lets handle it here

		//the ptr is our state machine friend yo!
		Wrapper* wrapper = (httpd::Wrapper*)(*ptr);

		if(!wrapper->get_request()->get_has_post_data()) {

			//the request wasn't post so we haven't handled it.  lets handle it now

			//hand off to the front controller
			server->front_controller(wrapper->get_request(), wrapper->get_response());

		} else {

			MHD_destroy_post_processor(wrapper->get_request()->get_post_processor());

		}

		//return the response after it's been routed to a controller
		result = wrapper->get_response()->get_mhd_result();

		delete wrapper;

		*ptr = NULL;

	}

	return result;

}

int httpd::HttpServer::request_header_builder(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {

	if(kind == MHD_HEADER_KIND) {

		//lets add the header to the request 
		((HttpRequest*)cls)->add_header(std::string(key), std::string(value));

	} else if( kind == MHD_GET_ARGUMENT_KIND ) {

		//lets add GET arg
		((HttpRequest*)cls)->add_ga(std::string(key), std::string(value));

	}

	return MHD_YES;

}

int httpd::HttpServer::post_processor (void *cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type,
		const char *transfer_encoding, const char *data, uint64_t off, size_t size) {


	Wrapper *wrapper = (Wrapper*)(cls);
	wrapper->get_server()->front_controller(wrapper->get_request(), wrapper->get_response(), filename, content_type, transfer_encoding, data, off, size);

	return MHD_YES;

}


void httpd::HttpServer::front_controller(HttpRequest* request, HttpResponse* response) {

	std::unordered_map<std::string, HttpRequestHandler*>::const_iterator got = endpoint_handlers.find(request->get_header("req_url"));

	if( got != endpoint_handlers.end()) {

		//if the key exists then lets handle stuff
		endpoint_handlers[request->get_header("req_url")]->handle(*request, *response);

	}


}

void httpd::HttpServer::front_controller(HttpRequest* request, HttpResponse* response, const char *filename, const char *content_type,
		const char *transfer_encoding, const char *data, uint64_t off, size_t size) {

	std::unordered_map<std::string, HttpRequestHandler*>::const_iterator got = endpoint_handlers.find(request->get_header("req_url"));

	if( got != endpoint_handlers.end()) {

		//if the key exists then lets handle stuff
		endpoint_handlers[request->get_header("req_url")]->handle_streaming_post(*request, *response, std::string((filename == NULL) ? "" : filename),
				std::string((content_type == NULL) ? "" : content_type ), std::string((transfer_encoding == NULL) ? "" : filename), data, off, size);

	}

}


void httpd::HttpServer::register_handler(std::string path, HttpRequestHandler& handler) {

	endpoint_handlers[path] = &handler;

}


