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

test: test.o $(ROU)/factors.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o $(ROU)/solvers.o
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) $(ROU)/factors.o $(OBJ)/vector.o $(OBJ)/matrix.o $(OBJ)/error.o $(ROU)/solvers.o test.o -o test.out

# Compiles
vectest.o: vectest.cpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c vectest.cpp

test.o: test.cpp $(ROU)/factors.hpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp $(ROU)/solvers.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c test.cpp

$(ROU)/solvers.o: $(ROU)/solvers.cpp $(ROU)/solvers.hpp $(ROU)/factors.hpp $(OBJ)/matrix.hpp $(OBJ)/vector.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(ROU)/solvers.cpp -o $(ROU)/solvers.o

$(ROU)/factors.o: $(ROU)/factors.cpp $(ROU)/factors.hpp $(OBJ)/vector.hpp $(OBJ)/matrix.hpp $(OBJ)/error.hpp
	$(CXX) $(DEBUGFLAGS) $(INCLUDE) -c $(ROU)/factors.cpp -o $(ROU)/factors.o

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
	