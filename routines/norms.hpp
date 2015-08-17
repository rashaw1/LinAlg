/*
 *   Purpose: Library of vector and matrix norms
 *
 *   DATE           AUTHOR              CHANGES
 *   =====================================================================
 *   16/08/15       Robert Shaw         Original code
 *
 */

#ifndef NORMLIBRARYDEF
#define NORMLIBRARYDEF

#include "vector.hpp"
#include "matrix.hpp"
#include "error.hpp"
#include <cmath>
#include <iostream>

// Inner (dot) product of two vectors
template <class T>
T dot(const Vector<T>& u, const Vector<T>& v)
{
  T rVal; // Return value
  // Get lengths of vectors, check they match
  int usize = u.size();
  int vsize = v.size();
  if(usize == vsize){
    // Calculate inner product
    for (int i = 0; i < usize; i++){
      rVal += u(i)*v(i); // Round brackets return by value, not reference
    }
  } else { // Throw error, and return null vector
    throw( Error("VECDOT", "Vectors different sizes.") );
  }
  return rVal;
}

// Overloaded p-norm calculator for different vector types
// Default to 2-norm, p should be greater than 0, but no check is given
// the routine will just return 0.0 if p <= 0.
double norm(const dVector& u, int p = 2) 
{
  int usize = u.size();
  double rVal = 0.0; // Initialise return value
  for (int i = 0; i < usize; i++) {
    // Calculate (p-norm)^p
    rVal += std::pow(u(i), p);
  }
  rVal = std::pow(rVal, (1.0/p));
  return rVal;
}

#endif
