// Implements modified Gram-Schmidt routine

#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include "vroutines.hpp"

// Gram-Schmidt orthonormalises the array of vectors x, into the array of 
// vectors q, returning true if successful. 
bool dgegs(Vector* x, Vector* q, Matrix& r)
{
  const double PRECISION = 1E-12; // Set cut-off precision
  bool rVal = true; // Will only be changed to false if a problem occurs
  int dim = x[0].size(); // Get length of each vector
  try{
    // Start procedure
    r(0, 0) = pnorm(x[0]); // Calculate 2-norm of x_0
    if (r(0, 0) < PRECISION) { // Singular norm - algorithm fails
      rVal = false;
    } else {
      q[0] = (1.0/r(0,0))*x[0]; // Normalise x_0
      // Begin main loop
      Vector y(dim); // Store the un-normalised temp vector
      for(int j = 1; j < dim; j++){
	y = x[j];
	for(int i = 0; i < j; i++){
	  r(i, j) = inner(q[i], y); // qT*y
	  y = y - r(i, j)*q[i];
	}
	r(j, j) = pnorm(y); // 2-norm of y
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

  
    
