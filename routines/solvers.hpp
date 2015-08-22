/*
 *   Purpose: To define a number of solvers, particularly for linear
 *            equations of the form Ax = b.
 * 
 *   DATE             AUTHOR            CHANGES
 *   ===============================================================
 *   21/08/15         Robert Shaw       Original code
 *
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
Vector qrsolve(const Matrix& A, const Vector& b); 

// Solve the full-rank least squares problem by QR factorisation
// Ax = y with A being an m x n matrix, m > n
Vector qrsquares(const Matrix& A, const Vector& b);

// Solve the square Ax = b problem by LU decomposition, i.e 
// Gaussian elimination with partial pivoting
Vector lusolve(const Matrix& A, const Vector& b);
