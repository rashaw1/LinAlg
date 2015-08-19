# # # # # # # # # # # # # # # # # 
# Makefile using g++ 		#
# # # # # # # # # # # # # # # # #

CXX = g++
CXXFLAGS = -O3 -Wall
DEBUGFLAGS = -g -Wall
INCLUDE = -I./objects -I./routines
OBJ = ./objects
ROU = ./routines

# Link
vectest: vectest.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o 
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) vectest.o $(OBJ)/error.o $(OBJ)/vector.o $(OBJ)/matrix.o -o vectest.out

test: test.o $(ROU)/vroutines.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) $(ROU)/vroutines.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o test.o -o test.out

# Compiles
vectest.o: vectest.cpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c vectest.cpp

test.o: test.cpp $(ROU)/vroutines.hpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c test.cpp

$(ROU)/vroutines.o: $(ROU)/vroutines.cpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(ROU)/vroutines.cpp -o $(ROU)/vroutines.o

$(OBJ)/matrix.o: $(OBJ)/matrix.cpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp $(OBJ)/vector.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/matrix.cpp -o $(OBJ)/matrix.o

$(OBJ)/vector.o: $(OBJ)/vector.cpp $(OBJ)/vector.hpp $(OBJ)/error.hpp $(OBJ)/matrix.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/vector.cpp -o $(OBJ)/vector.o

$(OBJ)/error.o: $(OBJ)/error.cpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(OBJ)/error.cpp -o $(OBJ)/error.o

# Clean
clean:
	@rm *.o
	@rm -f $(OBJ)/*.o
	@rm -f $(ROU)/*.o
	