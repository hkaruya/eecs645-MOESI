
FLAGS = -std=c++11 -g -Wall 
objects = main.o cache.o dm-processor.o Bus.o

process_sim: $(objects)
	g++ $(FLAGS) $(objects) -o process_sim
main.o: main.cpp
	g++ $(FLAGS) -c main.cpp
cache.o: cache.cpp
	g++ $(FLAGS) -c cache.cpp
dm-processor.o: dm-processor.cpp
	g++ $(FLAGS) -c dm-processor.cpp
Bus.o: Bus.h
	g++ $(FLAGS) -c Bus.cpp
clean: 
	rm *.o process_sim
