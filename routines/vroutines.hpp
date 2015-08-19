/*
 *    Purpose: Declare the signatures of several vector-based routines
 * 
 *    DATE                AUTHOR               CHANGES
 *    =================================================================
 *    19/08/15            Robert Shaw          Original code.
 * 
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
bool dgegs(const Matrix& x, Matrix& q, Matrix& r, const double PRECISION); 
