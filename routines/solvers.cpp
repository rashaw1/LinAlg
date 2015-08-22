// Implements solvers.hpp

#include "factors.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"

// Back substitution of the triangular system Rx = y
Vector backsub(const Matrix& R, const Vector& y)
{
  int dim = R.nrows(); // Triangular matrices must be square
  Vector rvec(dim); // Return vector
  // Begin algorithm
  double sum; // For storing the summation step in each loop
  for (int k = dim-1; k > -1; k--){
    // Add contributions from all previously determined entries
    sum = 0.0;
    for (int i = k+1; i < dim; i++){
      sum += rvec(i)*R(k, i);
    }
    // Determine final value
    rvec[k] = (y(k) - sum)/R(k, k);
  }
  return rvec;
}

// Solve the linear system Ax = b, using Householder-based QR
// factorisation, and backsub. Returns the solution vector x.
// Assumes A is square and nonsingular.
Vector qrsolve(const Matrix& A, const Vector& b)
{
  int dim = A.nrows();
  Vector x(dim); // For returning the answer
  Matrix v; Matrix r; // For the Householder algorithm
  // dgehh resizes v and r for us, so they
  // need only be declared here as null vectors.

  // QR Factorise A into v and r
  if(dgehh(A, r, v)){
    // Construct y = Q(T)b (x is y to save space)
    x = b; // Copy b into x
    implicitqtb(v, x);
    // Solve Rx = y by backsubstitution
    x  = backsub(r, x);
  } else {
    throw( Error("QRFACT", "Householder triangularisation unsuccesful.") );
  }
  return x;
}

// Use QR factorisation to solve the full-rank least-squares problem
Vector qrsquares(const Matrix& A, const Vector& b)
{
  int m = A.nrows();
  int n = A.ncols();
  Vector x(n); // Solution vector
  if ( m < n ) {
    throw( Error("QRSQRS", "Least squares problem is rank-deficient.") );
  } else {
    Matrix r; Matrix v;
    // Get the QR factorisation
    if(dgehh(A, r, v)){
      x = b; // Store b in x for convenience
      implicitqtb(v, x); // Calculate Q(T)b
      // Reduce the R matrix and Q(T)b vector
      for (int i = m-1; i > n-1; i--){
	r.removeRow(i);
      }
      x.resizeCopy(n);
      x = backsub(r, x);
    }
  }
  return x;
}

// Use the LU decomposition (Gaussian elimination with partial pivoting)
// to solve the system Ax = b. First, PA = LU is formed, and so we must 
// solve PAx = Pb. Pb is formed by implicitpb, then we can solve LUx = Pb
// first by forward substitution Ly = Pb for  y = Ux, then solve Ux = y
// by back substitution for x
Vector lusolve(const Matrix& A, const Vector& b)
{
  int dim = A.nrows(); // Assume square
  Vector x(dim); // Will contain the solution
  // First, LU decompose A
  Vector p(dim-1);
  Matrix B(dim, dim);
  p = dgelu(A, B);
  // Calculate Pb implicitly
  x = b;
  implicitpb(p, x);
  // Solve Ly = Pb by forward substitution
  // remebering diagonal of L is all ones
  for (int i = 1; i < dim; i++){
    double sum = 0.0;
    for (int j = 0; j < i; j++){
      sum += B(i, j)*x[j];
    }
    x[i] = x[i] - sum;
  }
  // Now we need to solve Ux = y for x
  // First remove L from B, to get U
  for(int i = 1; i<dim; i++){
    for (int j = 0; j < i; j++){
      B(i, j) = 0.0;
    }
  }
  // Backsubstitute to get x
  x = backsub(B, x);
  return x;
}
  

      
      
