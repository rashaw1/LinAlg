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
// Which takes a set of vectors x and returns them as the set of 
// orthogonal vectors q, whilst generating the transform matrix r
// Returns true if successful, false if failed
bool dgegs(Vector* x, Vector* q, Matrix& r); 
