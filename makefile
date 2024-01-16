bin/analog: obj/analog.o obj/logs.o
	c++ -std=c++14 -O3 obj/analog.o obj/logs.o -o bin/analog

obj/analog.o: src/analog.cpp
	c++ -std=c++14 -O3 -c src/analog.cpp -o obj/analog.o

obj/logs.o: src/logs.cpp src/logs.h
	c++ -std=c++14 -O3 -c src/logs.cpp -o obj/logs.o