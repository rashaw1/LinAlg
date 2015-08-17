// Tester program for Vector class

#include <iostream>
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include <iomanip>
#include <cmath>

int main(int argc, char* argv[])
{
  Vector dVec(5);
  Matrix m(3, 3);
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      m(i, j) = double(j - i) * 0.34;
    }
  }
  dVec.resize(3);
  dVec[0] = 0.56; dVec[1] = 1.32; dVec[2] = 0.87;
  std::cout << m(0, 0) << "  " << m(0, 1) << "  " << m(0, 2) << "\n";
  std::cout << dVec[0] << "  " << dVec[1] << "  " << dVec[2] << "\n";  
  try {
    dVec = dVec*m;
  } catch( Error e) {
    e.print();
  }
  for (int i = 0; i < 3; i++){
    std::cout << "d( " << i << " ) = " << std::setprecision(12) <<  dVec[i] << "\n";
  }
  return 0;
}
