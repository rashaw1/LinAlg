# # # # # # # # # # # # # # # # # 
# Makefile using g++ 		#
# # # # # # # # # # # # # # # # #

CXX = g++
CXXFLAGS = -O3 -Wall
DEBUGFLAGS = -g -Wall
INCLUDE = -I./objects
OBJ = ./objects

# Link
vectest: vectest.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o 
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) vectest.o $(OBJ)/error.o $(OBJ)/vector.o $(OBJ)/matrix.o -o vectest.out

# Compiles
vectest.o: vectest.cpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c vectest.cpp

$(OBJ)/matrix.o: $(OBJ)/matrix.cpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/matrix.cpp -o $(OBJ)/matrix.o

$(OBJ)/vector.o: $(OBJ)/vector.cpp $(OBJ)/vector.hpp $(OBJ)/error.hpp $(OBJ)/matrix.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/vector.cpp -o $(OBJ)/vector.o

$(OBJ)/error.o: $(OBJ)/error.cpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/error.cpp -o $(OBJ)/error.o
