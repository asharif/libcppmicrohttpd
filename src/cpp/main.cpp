#include <iostream>
#include <http_server.hpp>
#include <default_handler.hpp>

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 8080
#endif

#ifndef DEFAULT_THREAD_POOL_SIZE
#define DEFAULT_THREAD_POOL_SIZE 4
#endif

void configure_log4cpp();

int main(int argc, char *argv[]) {

	using namespace std;
	using namespace httpd;

	try {

		cout << "Starting server on port 8080 with a threadpool size of 4" << endl;

		//start the server on port (port), a threadpool (tp), and a buffer for upload data (1MiB)
		HttpServer server(DEFAULT_PORT, DEFAULT_THREAD_POOL_SIZE, 1048576);
		DefaultHandler default_handler;
		server.register_handler("/", default_handler);
		server.start();
		
	} catch(exception &e) {

		cerr << (e.what()) << endl;

	}

}
