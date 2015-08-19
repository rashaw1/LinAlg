// Test out the libraries

#include "vroutines.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "error.hpp"
#include <iostream>

int main(int argc, char* argv[]){
  Vector* x = new Vector[3];
  Vector* q = new Vector[3];
  Vector x0(3), x1(3), x2(3);
  Matrix r(3, 3);
  x0[0] = 1.0;
  x0[1] = 0.0;
  x0[2] = 2.0;
  x1[0] = 2.0;
  x1[1] = 3.0;
  x1[2] = 0.0;
  x2[0] = 4.0;
  x2[1] = 2.0;
  x2[2] = 1.0;
  x[0] = x0; x[1] = x1; x[2] = x2;
  if(dgegs(x, q, r)){
    for (int i = 0; i < 3; i++){
      std::cout << q[0][i] << "\t" << q[1][i] << "\t" << q[2][i] << "\n";
    }
  } else {
    std::cout << "Routine failed!\n";
  }
  std::cout << inner(q[0], q[1]) << "\n";
  std::cout << inner(q[0], q[2]) << "\n";
  std::cout << inner(q[1], q[2]) << "\n";
  delete[] x;
  delete[] q;
  return 0;
}
