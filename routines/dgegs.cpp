// Implements modified Gram-Schmidt routine

#include <iostream>
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include "norms.hpp"

// Gram-Schmidt orthonormalises the array of vectors x, into the array of 
// vectors q, returning true if successful. 
bool dgegs(dVector* x, dVector* q, dMatrix& r)
{
  const double PRECISION = 1E-12; // Set cut-off precision
  bool rVal = true; // Will only be changed to false if a problem occurs
  int dim = x[0].size(); // Get length of each vector
  //dMatrix r(dim, dim); // Define a square metrix to stroe the transform vectors
  try{
    // Start procedure
    r(0, 0) = norm(x[0]); // Calculate 2-norm of x_0
    if (r(0, 0) < PRECISION) { // Singular norm - algorithm fails
      rVal = false;
    } else {
      q[0] = (1.0/r(0,0))*x[0]; // Normalise x_0
      // Begin main loop
      dVector y(dim); // Store the un-normalised temp vector
      for(int j = 1; j < dim; j++){
	y = x[j];
	for(int i = 0; i < j; i++){
	  r(i, j) = dot<double>(q[i], y); // qT*y
	  y = y - r(i, j)*q[i];
	}
	r(j, j) = norm(y); // 2-norm of y
	if (r(j, j) < PRECISION) { 
	  rVal = false; 
	  break; 
	} else {
	  // Normalise y into q
	  q[j] = (1.0/r(j, j))*y;
	}
      }
    }
  } catch( Error e ) { 
    e.print();
  }
  return rVal;
}

// Test it out
int main(int argc, char* argv[]){
  dVector* x = new dVector[3];
  dVector* q = new dVector[3];
  dVector x0(3), x1(3), x2(3);
  dMatrix r(3, 3);
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
  std::cout << dot<double>(q[0], q[1]) << "\n";
  std::cout << dot<double>(q[0], q[2]) << "\n";
  std::cout << dot<double>(q[1], q[2]) << "\n";  
  delete[] x;
  delete[] q;
  return 0;
}
  
    
