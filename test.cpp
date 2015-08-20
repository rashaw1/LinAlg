// Test out the libraries

#include "vroutines.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "error.hpp"
#include <iostream>

int main(int argc, char* argv[]){
  Matrix x(3, 3);
  Matrix q(3, 3);
  Matrix r(3, 3);
  x(0, 0) = 1.0; x(0, 1) = 1.0; x(0, 2) = 2.0;
  x(1, 0) = 2.0; x(1, 1) = 3.0; x(1, 2) = 3.0;
  x(2, 0) = 4.0; x(2, 1) = 2.0; x(2, 2) = 1.0;
  if(dgehh(x, r, q)){
    x.print();
    std::cout << "\n\n";
    q.print();
    std::cout << "\n\n";
    r.print();
    std::cout << "\n\n";
    q = implicitq(q);
    q.print();
  } else {
    std::cout << "Routine failed!\n";
  }
}
