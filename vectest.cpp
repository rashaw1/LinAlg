// Tester program for Vector class

#include <iostream>
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include <cmath>

int main(int argc, char* argv[])
{
  dVector dVec(5);
  iVector iVec;
  iVec.resize(5);
  std::cout << "dVec has size: " << dVec.size() << "\n";
  for(int i = 0; i < 5; i++){
    dVec[i] = sqrt(double(i+1)/2.0);
    iVec[i] = i*3;
  }
  dMatrix m(3, 3);
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      m(i, j) = double(j - i) * 0.34;
    }
  }
  try {
    dVector d = dVec*m;
  } catch(Error e) {
    e.print();
  }
  dVec = dVector(3);
  dVec[0] = 0.56; dVec[1] = 1.32; dVec[2] = 0.87;
  dVec = dVec*m;
  for (int i = 0; i < 3; i++){
    std::cout << "d( " << i << " ) = " << dVec[i] << "\n";
  }
  return 0;
}
