#!/bin/bash
g++ -c -I/opt/intel/cnc/0.9.001/include -pthread  -O3 -o compiled-cnc/temperature.o ./guides/cnc_context/temperature.cpp -lpqxx  -lpq -std=c++0x
g++ -pthread  -O3 -o pdxobservatory compiled-cnc/*.o -L/opt/intel/cnc/0.9.001/lib/intel64 -lcnc -lrt -ltbb -ltbbmalloc ./*.cpp ./guides/*.cpp  -lpqxx  -lpq -std=c++0x
