SHELL=/bin/bash
SRC=`pwd`/src/cpp/**
INC=-I `pwd`/include/ -I `pwd`/src/hpp/ -I $(BOOST_CPP_HOME) 
DYNAMIC_LIB=/usr/lib/x86_64-linux-gnu/libmicrohttpd.so $(BOOST_CPP_HOME)/stage/lib/libboost_program_options.so /usr/lib/liblog4cpp.so
BIN=bin/cppmicrohttpd
LIB=lib/libcppmicrohttpd.so

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
