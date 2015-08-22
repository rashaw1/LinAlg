/*
 *    Purpose: Declare the signatures of several matrix factorisation routines
 *             and any associated procedures.
 * 
 *    DATE                AUTHOR               CHANGES
 *    =================================================================
 *    19/08/15            Robert Shaw          Original code.
 *    20/08/15            Robert Shaw          Added Householder.
 */

// Declare forward dependencies
class Matrix;
class Vector;
class Error;

// Declare the modified Gram-Schmidt procedure
// which takes a set of vectors in a full-rank
// matrix x, returning the orthogonalised vectors
// in a matrix q, and the transformation matrix r.
// Returns true if successful.
bool dgegs(const Matrix& x, Matrix& q, Matrix& r, const double& PRECISION); 

// Declare the Householder procedure
// giving the R matrix (y) of the QR factorisation of the matrix x
// and a set of reflection vectors, v, from which the q matrix 
// could be constructed. Returns true if successful 
bool dgehh(const Matrix& x, Matrix& y, Matrix& v);
// Implicity form product Qx using v from HH decomp
void implicitqx(const Matrix& v, Vector& x);
// Or Q(T)b instead
void implicitqtb(const Matrix& v, Vector& b);
// Return the full Q matrix from the HH decomp
Matrix explicitq(const Matrix& v);
// Get the LU decomposition of A by Gaussian Elimination with 
// partial pivoting. This actually computes PA = LU, putting L, U
// into the matrix B, and returning a vector of the row interchanges.
Vector dgelu(const Matrix& A, Matrix& B);
// Explicitly form the matrix P from the output of dgelu
Matrix explicitp(const Vector& p);
// Implicitly form Pb, where b is a vector, and P is the permutation
// matrix from the Gaussian eliminiation
void implicitpb(const Vector& p, Vector& b); 
