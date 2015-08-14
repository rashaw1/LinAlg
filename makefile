vectest.o: vectest.cpp vector.hpp matrix.hpp error.hpp
	g++ -g -c vectest.cpp

vectest: vectest.o
	g++ -o vectest.out vectest.o