SHELL=/bin/bash
SRC=`pwd`/src/cpp/**
INC=-I `pwd`/include/ -I `pwd`/src/hpp/ -I /usr/local/Cellar/libmicrohttpd/0.9.47_1/include/ -I /usr/local/Cellar/boost/1.60.0_2/include/boost/ -I /usr/local/Cellar/log4cpp/1.1.1/include/
DYNAMIC_LIB=/usr/local/Cellar/libmicrohttpd/0.9.47_1/lib/libmicrohttpd.dylib /usr/local/Cellar/boost/1.60.0_2/lib/libboost_program_options.dylib /usr/local/Cellar/log4cpp/1.1.1/lib/liblog4cpp.dylib
BIN=bin/cppmicrohttpd
LIB=lib/libcppmicrohttpd.dylib

.PHONY: defalut

default: clean dir
	@g++-5 -std=c++14 -Wall -Ofast -c $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -std=c++14 -o $(BIN) tmp/obj/** $(DYNAMIC_LIB)
	@rm -rf tmp/

debug: clean dir
	@g++-5 -std=c++14 -Wall -g -c $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -std=c++14 -g -o $(BIN) tmp/obj/** $(DYNAMIC_LIB)

lib: clean dir
	@g++-5 -std=c++14 -Wall -c -fpic -Ofast $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -shared -o $(LIB) tmp/obj/** $(DYNAMIC_LIB)

lib-debug: clean dir
	@g++-5 -std=c++14 -Wall -g -c -fpic -Ofast $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -shared -o $(LIB) tmp/obj/** $(DYNAMIC_LIB)

dir:
	@mkdir -p bin/
	@mkdir -p tmp/obj/
	@mkdir -p lib/


clean:
	@rm -rf tmp/
	@rm -rf bin/**
	@rm -rf lib/**
