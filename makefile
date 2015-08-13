vectest.o: vectest.cpp vector.hpp
	g++ -g -c vectest.cpp

vectest: vectest.o
	g++ -o vectest vectest.o