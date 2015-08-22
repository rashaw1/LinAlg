/*
 *   Purpose: To define a number of solvers, particularly for linear
 *            equations of the form Ax = b.
 * 
 *   DATE             AUTHOR            CHANGES
 *   ===============================================================
 *   21/08/15         Robert Shaw       Original code
 *   22/08/15         Robert Shaw       Iterationive eigenv's  added.
 */

// Declare forward dependencies
class Vector;
class Matrix;
class Error;

// The basic back-substitution routine, which is used in pretty much
// every other solver. R is an upper triangular matrix, y is the 
// rhs vector - i.e., solving Rx = y, where x is the solution returned
Vector backsub(const Matrix& R, const Vector& y);

// Solve Ax = b by QR factorisation (using Householder algorithm)
// construct y = Q(T)b, by implicitqtb, then solve Rx = y by 
// back substitution. 
// First instance performs decomposition, second takes v from 
// already performed decomposition.
Vector qrsolve(const Matrix& A, const Vector& b); 
Vector qrsolve(const Matrix& R, const Matrix& v, const Vector& b);

// Solve the full-rank least squares problem by QR factorisation
// Ax = y with A being an m x n matrix, m > n
Vector qrsquares(const Matrix& A, const Vector& b);

// Solve the square Ax = b problem by LU decomposition, i.e 
// Gaussian elimination with partial pivoting. 
// First instance does decomposition, second instance
// takes already formed decomposition.
Vector lusolve(const Matrix& A, const Vector& b);
Vector lusolve(const Matrix& B, const Vector& p, const Vector& b);

// Solve the square, symmetric positive definite sytem Ax = b 
// using cholesky factorisation
// Second instance uses already formed factorisation - note
// that the arguments are reversed, to distinguish the two
Vector choleskysolve(const Matrix& A, const Vector& b);
Vector choleskysolve(const Vector& b, const Matrix& R);

// Use the power iteration algorithm to find an eigenvalue -
// specifically the eigenvalue with largest absolute value -
// of A given a (normalised) vector, v. The eigenvector is
// left in v. Returns the eigenvalue.
// Cuts off when PRECISION is reached, or MAXITER iterations done
double poweriter(const Matrix& A, Vector& v, double PRECISION = 1e-12, int MAXITER = 100);

// Use the inverse power iteration method to find the eigenvalue
// (and corresponding eigenvector) of A nearest to u, given a vector v.
// Returns the eigenvalue.
double inverseiter(const Matrix& A, Vector& v, double u, double PRECISION = 1e-12, int MAXITER=100);

// Use the Rayleigh Iteration Algorithm to get approximations for an eigenvec/val pair
// of a matrix A. Returns eigenvalue, stores vector in v.
double rayleigh(const Matrix& A, Vector& v, double l0, double PRECISION = 1e-8, int MAXITER = 50);
