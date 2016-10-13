SHELL=/bin/bash
SRC=`pwd`/src/cpp/**
INC=-I `pwd`/include/ -I `pwd`/src/hpp/ -I $(BOOST_CPP_HOME) 
SHARED_LIB_DEP=$(LIB_MICROHTTP_HOME)libmicrohttpd.so $(BOOST_CPP_HOME)/stage/lib/libboost_program_options.so $(LIB_LOG4CPP_HOME)/liblog4cpp.so
BIN=bin/cppmicrohttpd
SHARED_LIB=lib/libcppmicrohttpd.so
LINUX=`uname`

.PHONY: defalut, debug, lib, lib-debug

default: clean dir
	@g++-5 -std=c++14 -D$(LINUX) -Wall -Ofast -c $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -std=c++14 -o $(BIN) tmp/obj/** $(SHARED_LIB_DEP)
	@rm -rf tmp/

debug: clean dir
	@g++-5 -std=c++14 -Wall -D$(LINUX) -g -c $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -std=c++14 -g -o $(BIN) tmp/obj/** $(SHARED_LIB_DEP)
	@rm -rf tmp/

lib: clean dir
	@g++-5 -std=c++14 -Wall -D$(LINUX) -c -fpic -Ofast $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -shared -o $(SHARED_LIB) tmp/obj/** $(SHARED_LIB_DEP)

lib-debug: clean dir
	@g++-5 -std=c++14 -Wall -D$(LINUX) -g -c -fpic $(INC) $(SRC) 
	@mv *.o tmp/obj/
	@g++-5 -shared -o $(SHARED_LIB) tmp/obj/** $(SHARED_LIB_DEP)

dir:
	@mkdir -p bin/
	@mkdir -p tmp/obj/
	@mkdir -p lib/


clean:
	@rm -rf tmp/
	@rm -rf bin/**
	@rm -rf lib/**
