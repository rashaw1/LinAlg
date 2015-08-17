# # # # # # # # # # # # # # # # # 
# Makefile using g++ 		#
# # # # # # # # # # # # # # # # #

CXX = g++
CXXFLAGS = -O3 -Wall
DEBUGFLAGS = -g -Wall
INCLUDE = -I./objects
OBJ = ./objects
ROU = ./routines

# Link
vectest: vectest.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o 
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) vectest.o $(OBJ)/error.o $(OBJ)/vector.o $(OBJ)/matrix.o -o vectest.out

dgegs: $(ROU)/dgegs.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) $(ROU)/dgegs.o $(OBJ)/error.o $(OBJ)/vector.o $(OBJ)/matrix.o -o $(ROU)/dgegs.out

# Compiles
vectest.o: vectest.cpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c vectest.cpp

$(ROU)/dgegs.o: $(ROU)/dgegs.cpp $(ROU)/norms.hpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(ROU)/dgegs.cpp -o $(ROU)/dgegs.o

$(OBJ)/matrix.o: $(OBJ)/matrix.cpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/matrix.cpp -o $(OBJ)/matrix.o

$(OBJ)/vector.o: $(OBJ)/vector.cpp $(OBJ)/vector.hpp $(OBJ)/error.hpp $(OBJ)/matrix.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/vector.cpp -o $(OBJ)/vector.o

$(OBJ)/error.o: $(OBJ)/error.cpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/error.cpp -o $(OBJ)/error.o
