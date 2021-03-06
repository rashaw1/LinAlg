
// Test out the libraries

#include "factors.hpp"
#include "solvers.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "error.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]){
  Matrix x(5, 5);
  Matrix q(5, 5);
  Matrix r(5, 5);
  x(0, 0) = 11.0; x(0, 1) = 0.0; x(0, 2) = -3.0; x(0, 3) = 2.0; x(0,4) = 4.0;
  x(1, 0) = 5.0; x(1, 1) = 41.0; x(1, 2) = 7.0; x(1, 3) = 8.0; x(1, 4) = -9.0;
  x(2, 0) = 1.0; x(2, 1) = 1.0; x(2, 2) = 6.0; x(2, 3) = 1.0; x(2, 4) = 1.0;
  x(3, 0) = x(3, 1) = x(3, 2) = x(3, 4) = 0.0; x(3, 3) = 2.0;
  x(4, 0) = 2.0; x(4, 1) = -3.0; x(4, 2) = 2.0; x(4, 3) = -3.0; x(4, 4) = 18.0;
  Vector p(4);
  p = dgelu(x, r);
  if(p.size()==4){
    p.print();
    std::cout << "\n\n";
    r.print();
    std::cout << "\n\n";
    q = explicitp(p);
    q.print();
    std::cout << "\n\n";
    Vector b(5);
    b[0] = 4.0; b[1] = 3.0; b[2] = 5.0; b[3] = 1.0; b[4] = 7.0;
    b = lusolve(x, b);
    b.print();
    std::cout << "\n\n";
    Matrix m2(3, 2);
    b.resize(3);
    m2(0, 0) = 3.0; m2(0, 1) = -6.0;
    m2(1, 0) = 4.0; m2(1, 1) = -8.0;
    m2(2, 0) = 0.0; m2(2, 1) = 1.0;
    b[0] = -1.0; b[1] = 7.0; b[2] = 2.0;
    b = qrsquares(m2, b);
    b.print();
    std::cout << "\n\n";
  } else {
    std::cout << "Routine failed!\n";
  }

  // Test 2 - Least squares
  Matrix A(100, 15);
  Vector t(100);
  Vector d(100);
  for (int i = 0; i < 100; i++){
    t[i] = double(i)/99.0;
    for (int j = 0; j < 15; j++){
      A(i, j) = std::pow(t(i), j);
    }
    d[i] = sin(4.0*t(i));
    d[i] = exp(d[i]);
  }
  d = d*(1.0/2006.787453080206);
  d = qrsquares(A, d);
  d.print();
  std::cout << "\n\n";
  // Test Hessenberg
  x.resize(5, 5);
  x(0, 0) = 1.0; x(0, 1) = 2.0; x(0, 2) = 3.0; x(0, 3) = 4.0; x(0, 4) = 2.0;
  x(1, 0) = 2.0; x(1, 1) = 5.0; x(1, 2) = 6.0; x(1, 3) = 7.0; x(1, 4) = 3.0;
  x(2, 0) = 3.0; x(2, 1) = 6.0; x(2, 2) = 5.0; x(2, 3) = 0.0; x(2, 4) = 4.0;
  x(3, 0) = 4.0; x(3, 1) = 7.0; x(3, 2) = 0.0; x(3, 3) = 8.0; x(3, 4) = 3.0;
  x(4, 0) = 2.0; x(4, 1) = 3.0; x(4, 2) = 4.0; x(4, 3) = 3.0; x(4, 4) = 5.0;
  Matrix y; Matrix v;
  if (hessenberg(x, y, v)){
    x.print();
    std::cout << "\n\n";
    y.print();
    std::cout << "\n\n";
    v.print();
    std::cout << "\n\n";
    v = explicitq(v);
    v.print();
    std::cout << "\n\n";
    x = v*(y*v.transpose());
    x.print();
    std::cout << "\n\n";
  } else {
    std::cout << "Hessenberg failed.\n";
  }

  x.resize(5, 5);
  srand((unsigned) time(0));
  for (int i = 0; i < 5; i++){
    x(i, i) = rand()%10+1;
    for (int j = 0; j < i; j++){
      x(i, j) = x(j, i) = rand()%11;
    }
  }
  x.print();
  std::cout << "\n\n";
  Vector vals; Matrix vecs;
  if(symqr(x, vals, vecs, 1e-12)){
    vecs.print();
    std::cout << "\n\n";
    vals.print();
    std::cout << "\n\n";
  } else {
    std::cout << "QR shift failed\n";
  }

  // Test Cholesky
  x.resize(3, 3);
  x(0, 0) = x(1, 1) = x(2, 2) = 3.0;
  x(0, 1) = x(1, 0) = x(1, 2) = x(2, 1) = 2.0;
  x(0, 2) = x(2, 0) = 0.0;
  d.resize(3);
  d[0] = 1.0; d[1] = 3.0; d[2] = 2.0;
  d = choleskysolve(x, d);
  d.print();
  std::cout << "\n\n";

  // Test power method / inverse power method
  x(0, 0) = 1.0; x(0, 1) = 2.0; x(0, 2) = 3.0;
  x(1, 0) = 2.0; x(1, 1) = 2.0; x(1, 2) = 1.0;
  x(2, 0) = 3.0; x(2, 1) = 1.0; x(2, 2) = 1.0;
  d[0] = 1.0; d[1] = 1.0; d[2] = 1.0;
  double lam = rayleigh(x, d, 3.5, 1e-8, 100);
  std::cout << lam << "\n";
  d.print(1e-10);
  std::cout << "\n\n";

  x.assign(4, 4, 0.0);
  x(0, 0) = 4.99; x(0, 1) = x(1, 0) = -0.2236068; x(0, 2) = x(2, 0) = 0.0;
  x(1, 1) = -2.48056; x(1, 2) = x(2, 1) = -1.1029755; x(1, 3) = x(3, 1) = 0.0;
  x(2, 2) = -2.48056; x(2, 3) = x(3, 2) = -0.2236068; x(3, 3) = 4.99;
  if(symqr(x, vals, vecs, 1e-12)){
    vals.print();
    vecs.print();
  }
}
