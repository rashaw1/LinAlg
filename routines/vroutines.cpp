// Implements vroutines.hpp

#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include "vroutines.hpp"

// Gram-Schmidt orthonormalises the columns of x, into the column 
// vectors of q, whilst generating the transformation matrix r,
// returning true if successful. Gives QR factorisation.
bool dgegs(const Matrix& x, Matrix& q, Matrix& r, const double PRECISION)
{
  bool rVal = true; // Will only be changed to false if a problem occurs
  int dim = x.nrows(); // Assume that x is full rank
  // Start procedure
  // Get columns of x as an array of vectors
  Vector* xa = new Vector[dim];
  for (int i = 0; i < dim; i++) {
    xa[i] = x.colAsVector(i);
  }
  // Define a placeholder array of vectors for q
  Vector* qa = new Vector[dim];
  r(0, 0) = pnorm(xa[0]); // Calculate 2-norm of x_0
  if (r(0, 0) < PRECISION) { // Singular norm - algorithm fails
    rVal = false;
  } else {
    qa[0] = (1.0/r(0,0))*xa[0]; // Normalise x_0
    // Begin main loop
    Vector y(dim); // Temporary placeholder
    for(int j = 1; j < dim; j++){
      y = xa[j]; 
      for(int i = 0; i < j; i++){
        r(i, j) = inner(qa[i], y); // qT*y
        y = y - r(i, j)*qa[i];
      }
      r(j, j) = pnorm(y); // 2-norm of y
      if (r(j, j) < PRECISION) { 
        rVal = false; 
        break; 
      } else {
        // Normalise y into q
        qa[j] = (1.0/r(j, j))*y;
      }
    }
  }
  // Copy the vectors qa into q, and clean up memory
  for (int i = 0; i < dim; i++) {
    q.setCol(i, qa[i]);
  }
  delete[] xa;
  delete[] qa;
  return rVal;
}

  
    
