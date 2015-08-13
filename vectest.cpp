// Tester program for Vector class

#include <iostream>
#include "vector.hpp"
#include <cmath>

int main(int argc, char* argv[])
{
  Vector<double> dVec(5);
  Vector<int> iVec;
  iVec.resize(5);
  std::cout << "dVec has size: " << dVec.size() << "\n";
  for(int i = 0; i < 5; i++){
    dVec[i] = sqrt(double(i+1)/2.0);
    iVec[i] = i*3;
  }
  std::cout << dVec[0] << " " << dVec[4] << "\n";
  std::cout << iVec[2] << " " << iVec[3] << "\n";
  dVec = dVec+dVec;
  iVec = iVec*4;
  std::cout << dVec[0] << " " << dVec[4] << "\n";
  std::cout << iVec[2] << " " << iVec[3] << "\n";
  iVec.resizeCopy(8);
  std::cout << iVec[2] << " " << iVec.size() << "\n";
  return 0;
}
