// Implements vroutines.hpp

#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include "vroutines.hpp"
#include <iostream>

// Gram-Schmidt orthonormalises the columns of x, into the column 
// vectors of q, whilst generating the transformation matrix r,
// returning true if successful. Gives QR factorisation.
bool dgegs(const Matrix& x, Matrix& q, Matrix& r, const double& PRECISION)
{
  bool rVal = true; // Will only be changed to false if a problem occurs
  int dim = x.nrows(); // Assume that x is full rank
  // Make sure q and r are the appropriate sizes
  q.resize(dim, dim);
  r.resize(dim, dim);
  
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

// Householder factorisation algorithm, taking matrix x
// and transforming to the R matrix of QR factorisation
// returning a set of reflection vectors, v. Works on any 
// m x n matrix, with m >= n. 
bool dgehh(const Matrix& x, Matrix& y, Matrix& v)
{
  bool rVal = true; // Return value
  // Get dimensions of x
  int m = x.nrows();
  int n = x.ncols();
  // Make sure v and y are the same size as x
  v.resize(m, n); 
  y.resize(m, n);
  y = x;

  // Start main algorithm
  double value = 0.0; // Placeholder for norms
  for (int k = 0; k < n; k++){
    // Make temporary vector and matrix for subvector/matrix of x
    Vector column(m-k);
    Matrix subx(m-k, n-k);
    // Copy in values
    for (int i = k; i < m; i++){
      column[i-k] = y(i, k);
      for (int j = k; j < n; j++){
      	subx(i-k, j-k) = y(i, j);
      }
    }
    // Compute the reflector
    value = pnorm(column);
    value = (column(0) < 0 ? -value : value);
    column[0] = column(0)+ value;
    value = pnorm(column);
    column = (1.0/value)*column;

    // Transform the submatrix
    Vector temporary(n-k);
    temporary = column*subx;
    Matrix transx(m-k, n-k);
    transx = outer(column, temporary);
    subx = subx - 2.0*transx;

    // Transfer values to output matrices
    for (int i = 0; i < k; i++){
      v(i, k) = 0.0;
    }
    for (int i = k; i < m; i++){
      v(i, k) = column(i-k);
      for (int j = k; j < n; j++){
	y(i, j) = subx(i-k, j-k);
      }
    } 
  }
  return rVal;
}

// Take the matrix v from the HH decomposition and implicitly
// calculate the product of Q with a vector x, returned in x.
void implicitqx(const Matrix& v, Vector& x)
{
  int m = v.nrows();
  int n = v.ncols();
  // Begin main loop
  for (int k = n-1; k >= 0; k--) {
    Vector temp(m-k); // Temporary vector of correct size
    Vector vk(m-k); 
    // Transfer values
    for (int i = 0; i < m-k; i++){
      temp[i] = x(i+k);
      vk[i] = v(i+k, k);
    }
    // Compute the product
    double dval = inner(vk, temp);
    vk = dval*vk;
    temp = temp - 2.0*vk;
    // Copy values back to output
    for (int i = 0; i < m-k; i++){
      x[i+k] = temp(i);
    }
  }
}

// Calculate the product Q(T)b of the Q matrix using the HH
// decomposition, with a vector b - implicitly, i.e. without
// ever forming Q
void implictqtb(const Matrix& v, Vector& b)
{
  int m = v.nrows();
  int n = v.ncols();
  // Begin main loop
  for (int k = 0; k < n; k++) {
    Vector temp(m-k); // Temporary vector for subvector of b
    Vector vk(m-k); 
    // Copy values in
    for (int i = k; i < m; i++) {
      temp[i-k] = b(i);
      vk[i-k] = v(i-k, k);
    }
    double dval = inner(vk, temp);
    vk = dval*vk;
    temp = temp - 2.0*vk;
    // Copy values back to output
    for (int i = k; i < m; i++) {
      b[i] = temp(i-k);
    }
  }
}   

// Form explicitly the Q matrix from the HH decomposition
Matrix implicitq(const Matrix& v)
{
  int m = v.nrows();
  int n = v.ncols();
  Matrix rmat(m, n); // Return matrix
  // Do implicitqx for x = the identity vector in each dimension
  for (int i = 0; i < n; i++) {
    Vector temp(n, 0.0); // Temporary vector of all zeroes
    temp[i] = 1.0; // Turn into the identity
    implicitqx(v, temp); // Get the ith column of q
    rmat.setCol(i, temp); // Set the ith column of q 
  }
  return rmat;
}
  
