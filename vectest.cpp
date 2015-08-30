// Tester program

#include <iostream>
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
  srand((unsigned)time(0));
  Vector dVec(5);
  Matrix m(3, 3);
  m(0, 0) = -1.0; m(0, 1) = 1.0; m(0, 2) = 2.0;
  m(1, 0) = 2.0; m(1, 1) = 3.0; m(1, 2) = 3.0;
  m(2, 0) = 4.0; m(2, 1) = 2.0; m(2, 2) = 1.0;
  m.print();
  dVec.resize(3);
  dVec[0] = 0.78045432; dVec[1] = 0.27960367; dVec[2] = 0.55920734;
  Vector d2(3);
  d2 = dVec*m;
  d2.print();
  std::cout << "\n\n\n";
  d2[0] = 3.5765; d2[1] = 2.7377; d2[2] = 2.9590;
  m = outer(dVec, d2);
  std::cout << "\n\n outer product \n\n";
  m.print();
  std::cout << "\n\n\n";
  dVec.print();

  dVec.resize(20);
  for (int i = 0; i < 20; i++){
    dVec[i] = rand()%100 + 1;
  }
  dVec.print();
  dVec.sort();
  dVec.print();
  int dim = 5;
  double PRECISION = 1e-12;
  Vector v(dim);
  v[0] = 0.0; v[1] = 5.4; v[2] = 3.2; v[3] = 0.0; v[4] = 4.1;
  Matrix P(dim, dim, 0.0);
  for (int j = 0; j < dim; j++) { P(j, j) = 1.0; } // Turn into identity                                                                                         
  int k= dim-1; // Keep track of last non-zero entry                                                                                                            
  for (int j = dim-1; j > -1; j--){ // Start at bottom and work up                                                                   
    if (fabs(v(j))< PRECISION && k!=j ){
      std::cout << "\n Found a zero. \n";
      // And swap the two rows                                                                                                                                   
      P.swapRows(j, k);
      k--;
    }
  }
  std::cout << "\n\n";
  P.print();
  v = P*v;
  std::cout << "\n\n";
  v.print();

  return 0;
}
