// Implements solvers.hpp

#include "factors.hpp"
#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include <cmath>

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

// Second instance does the same as above, but is given the matrices R and v as
// arguments, so repeated decompositions can be avoided.
Vector qrsolve(const Matrix& R, const Matrix& v, const Vector& b)
{
  Vector x(b.size()); // Solution vector
  x = b; // Initialise x to b
  implicitqtb(v, x); // Calculate Q(T)b implicitly
  // Solve Rx = y = Q(T)b by backsub
  x = backsub(R, x);
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
  // remembering diagonal of L is all ones
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

// Do the same as above, but with already formed LU decomp so as to
// avoid the need for repeated decompositions
Vector lusolve(const Matrix& B, const Vector& p, const Vector& b)
{
  int dim = b.size();
  Vector x(dim); // Solution vector
  x = b;
  implicitpb(p, x); // Calculate Pb implicitly
  // Solve Ly = Pb by forward substitution                                                     // remembering diagonal of L is all ones                                      
  for (int i = 1; i < dim; i++){
    double sum = 0.0;
    for (int j = 0; j < i; j++){
      sum += B(i, j)*x[j];
    }
    x[i] = x[i] - sum;
  }
  // Now we need to solve Ux = y for x                     
  // First remove L from B, to get U
  Matrix U;
  U = B;
  for(int i = 1; i<dim; i++){
    for (int j = 0; j < i; j++){
      U(i, j) = 0.0;
    }
  }
  // Then solve by backsub
  x = backsub(U, x);
  return x;
}


// Solve the linear system Ax = b, where A is real symmetric
// positive definite, using Cholesky decomposition
// The algorithm is A = R(T)R by decomposition, so we solve
// R(T)Rx = b - so solve the lower triangular R(T)y = b
// by forward substitution, then solve the upper triangular
// Rx = y by back substitution.
Vector choleskysolve(const Matrix& A, const Vector& b)
{
  int dim = A.nrows(); // Assume square
  Vector x(dim); // Solution vector
  Matrix R;
  R = cholesky(A); // Get the upper triangular matrix R
  // Do the forward substitution for y
  x = b; // Initialise x
  for (int i = 0; i < dim; i++){
    double sum = 0.0;
    for (int j = 0; j < i; j++){
      sum += R(j, i)*x[j]; // We need the transpose of R
    }
    x[i] = x[i] - sum;
    x[i] = x[i]/R(i, i); // Normalise
  }
  // Now do the back substitution
  x = backsub(R, x);
  return x;
}

// Do the same as above where the decomposition is already given -
// note the arguments are reversed
Vector Cholesky(const Vector& b, const Matrix& R)
{
  int dim = b.size();
  Vector x(dim); // Solution vector
  x = b;
  // Do the forward substitution for y 
  for (int i = 0; i < dim; i++){
    double sum = 0.0;
    for (int j = 0; j < i; j++){
      sum += R(j, i)*x[j]; // We need the transpose of R           
    }
    x[i] = x[i] - sum;
    x[i] = x[i]/R(i, i); // Normalise                                                   
  }
  // Now do the back substitution                                         
  x = backsub(R, x);
  return x;
}

// The power iteration method for finding the largest absolute 
// valued eigenvalue of a matrix A, given a normalised vector v.
double poweriter(const Matrix& A, Vector& v, double PRECISION, int MAXITER)
{
  Vector w; // Temporary vector for intermediate steps
  int dim = v.size();
  double norm = pnorm(v);
  double lambda = 0.0; // The eigenvalue 
  if(norm - 1.0 > PRECISION) { // Normalise if not already
    v = (1.0/norm)*v;
  }
  // Begin loop
  double dist = 1.0; // Track distance between eigenvalue at each iter
  double err = 1.0; // Track error - max of dist and norm
  double oldlambda = 0.0; // Store the old lambda value for error calc
  int iter = 0; // Track number of iterations
  Vector oldv;
  while(err > PRECISION && iter < MAXITER){
    oldv = v; // Store previous vector
    w = A*v; // Calculat Av
    v = w;
    w.sort(); // Sort w without changing v
    // The best guess for the eigenvalue is the largest by absolute value
    // member of w
    lambda = (fabs(w(0)) > fabs(w(dim-1)) ? w(0) : w(dim-1));
    v = (1.0/lambda)*v;
    dist = fabs(lambda - oldlambda);
    norm = pnorm(v-oldv);
    err = (norm < dist ? dist : norm);
    oldlambda = lambda;
    iter++;
  }
  return lambda;
}

// Do the inverse power iteration to find the eigenvalue closest to u, and the
// corresponding eigenvector (stored in v). Uses lusolve.
double inverseiter(const Matrix& A, Vector& v, double u, double PRECISION, int MAXITER)
{
  Vector w; // Temporary vector for intermediate steps                              
  int dim = v.size();
  double norm = pnorm(v);
  double lambda = 0.0; // The eigenvalue                                   
  if(norm - 1.0 > PRECISION) { // Normalise if not already                     
    v = (1.0/norm)*v;
  }
  // Form the matrix A-uI and LU decompose
  Matrix X(dim, dim);
  X = A;
  for (int i = 0; i < dim; i++){
    X(i, i) -= u;
  }
  Matrix B; Vector p; // Will store the LU decomposition
  p = dgelu(X, B);
  // Begin loop                                                                   
  double dist = 1.0; // Track distance between eigenvalue at each iter                  
  double err = 1.0; // Track error - max of dist and norm                            
  double oldlambda = 0.0; // Store the old lambda value for error calc              
  int iter = 0; // Track number of iterations                                 
  Vector oldv;
  while(err > PRECISION && iter < MAXITER){
    oldv = v; // Store previous vector                                            
    w = lusolve(B, p, v); // Solve (A-uI)w = v for w
    v = w;
    w.sort();
    lambda = (fabs(w(0)) > fabs(w(dim-1)) ? w(0) : w(dim-1));
    v = (1.0/lambda)*v;
    lambda = (1.0/lambda) + u;
    dist = fabs(lambda - oldlambda);
    norm = pnorm(v-oldv);
    err = (norm < dist ? dist : norm);
    oldlambda = lambda;
    iter++;
  }
  return lambda;
}  

// Rayleigh quotient iteration to get fast convergence to an eigenvalue
// eigenvector pair. Takes the matrix A for which eigenv's are needed,
// a starting guess eigenvec v, a starting guess value l0, and cutoff criteria.
// Returns eigenvalue, stores vector in v.
double rayleigh(const Matrix& A, Vector& v, double l0, double PRECISION, int MAXITER)
{
  double lambda = 0.0;
  double mu = l0;
  v = (1.0/pnorm(v))*v;
  // Form A - mu*I
  Matrix X;
  X = A;
  for (int i = 0; i < A.nrows(); i++){
    X(i, i) = X(i, i) - mu;
  }
  // Solve Xy = v for y
  Vector y;
  y = lusolve(X, v);
  lambda = inner(y, v);
  mu = mu + (1.0/lambda);
  double err = pnorm(y-lambda*v)/(pnorm(y));
  int iter = 0;
  while (err > PRECISION && iter < MAXITER){
    v = (1.0/pnorm(y))*y;
    // Form A - mu*I
    X = A;
    for (int i = 0; i < A.nrows(); i++){
      X(i, i) = X(i, i) - mu;
    }
    // Solve Xy = v
    y = lusolve(X, v);
    lambda = inner(y, v);
    mu = mu + (1.0/lambda);
    err = pnorm(y-lambda*v)/pnorm(y);
    iter++;
  }
  return mu;
}
