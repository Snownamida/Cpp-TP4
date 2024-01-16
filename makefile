bin/analog: obj/analog.o obj/logs.o obj/document.o obj/documents.o
	c++ -std=c++14 -O3 obj/analog.o obj/logs.o obj/document.o obj/documents.o -o bin/analog

obj/analog.o: src/analog.cpp
	c++ -std=c++14 -O3 -c src/analog.cpp -o obj/analog.o

obj/logs.o: src/logs.cpp src/logs.h
	c++ -std=c++14 -O3 -c src/logs.cpp -o obj/logs.o

obj/document.o: src/document.cpp src/document.h
	c++ -std=c++14 -O3 -c src/document.cpp -o obj/document.o

obj/documents.o: src/documents.cpp src/documents.h
	c++ -std=c++14 -O3 -c src/documents.cpp -o obj/documents.o