
FLAGS = -std=c++11 -g -Wall 
template_files = data-collect.h data-collect.hpp
objects = main.o front-end.o cache.o dm-processor.o lru-processor.o processor-manager.o MOESI.o MOESI-Data.o Bus.o

process_sim: $(objects)
	g++ $(FLAGS) $(objects) -o process_sim
main.o: main.cpp $(template_files)
	g++ $(FLAGS) -c main.cpp
front-end.o: front-end.cpp
	g++ $(FLAGS) -c front-end.cpp
cache.o: cache.cpp
	g++ $(FLAGS) -c cache.cpp
dm-processor.o: dm-processor.cpp
	g++ $(FLAGS) -c dm-processor.cpp
lru-processor.o: lru-processor.cpp
	g++ $(FLAGS) -c lru-processor.cpp 
processor-manager.o: processor-manager.cpp
	g++ $(FLAGS) -c processor-manager.cpp
MOESI.o: protocol.h MOESI.cpp
	g++ $(FLAGS) -c MOESI.cpp
MOESI-Data.o: MOESI-Data.cpp data-collect.h
	g++ $(FLAGS) -c MOESI-Data.cpp
Bus.o: Bus.cpp
	g++ $(FLAGS) -c Bus.cpp
clean: 
	rm *.o process_sim
