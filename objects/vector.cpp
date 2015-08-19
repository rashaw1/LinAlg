/*
 *   Implementation of vector.hpp
 *
 *   DATE               AUTHOR                  CHANGES
 *   ============================================================================
 *   14/08/15           Robert Shaw             Original code.
 *   15/08/15           Robert Shaw             Added error handling.
 *   19/08/15           Robert Shaw             Added p-norm and dot product.
 */
 
 #include "vector.hpp"
 #include <cmath>
#include <iostream>
#include <iomanip>
 
// Memory clean up function
void Vector::cleanUp()
{
  // if n = 0, no memory was ever allocated!
  if ( size() > 0 ) {
    delete[] v;
  }
}

// Constructors
Vector::Vector(int length)
{
  n = length; // Set length of vector
  if(length > 0){ // Allocate memory
    v = new double[length];
  } else {
    v = NULL;
  }
}


Vector::Vector(int length, const double& a)
{
  n = length; // Set length of vector
  if(length > 0){ // Allocate memory and set all values to a
    v = new double[length];
    for(int i=0; i<length; i++){
      v[i] = a;
    }
  } else {
    v = NULL;
  }
}


Vector::Vector(int length, const double* a)
{
  n = length; // Set length
  if (length > 0) { // Allocate memory, and copy a into vector
    v = new double[length];
    for(int i = 0; i < length; i++){
      v[i] = a[i]; // Really hope that a is the right length!
    }
  } else {
    v = NULL;
  }
}

// Copy constructor

Vector::Vector(const Vector& u)
{
  n = u.size(); // Get size
  if(n > 0) { // Allocate size, and copy in values
    v = new double[n];
    for (int i = 0; i < n; i++) {
      v[i] = u.v[i];
    }
  } else {
    v = NULL;
  }
}

// Destructor

Vector::~Vector()
{
  cleanUp(); // Deallocate memory if necessary
}

// Shaping functions

void Vector::resize(int length) // Resize with loss of values
{
  cleanUp(); // Deallocate old memory
  n = length; // Reset size
  if (length > 0) { // Reallocate memory
    v = new double[length];
  } else {
    v = NULL;
  }
}


void Vector::resizeCopy(int length) { 
  // Resizes, keeping as many values as fit
  double* tempV;
  if ( n > 0 ) {
    tempV = new double[n]; // Store old values
    for (int i = 0; i < n; i++) {
      tempV[i] = v[i];
    }
  }
  // Do the resizing
  resize(length);
  // Copy in old values as far as fits, leaving excess empty
  if ( n > 0 ) {
    int m = ( n < length ? n : length ); // m is the lesser of n, length
    for (int i = 0; i < m; i++) {
      v[i] = tempV[i];
    }
  }
}


void Vector::assign(int length, const double& a) // Resizes, setting all vals to a
{
  // Do resizing
  resize(length);
  // Set values to a
  if ( length > 0 ) {
    for(int i = 0; i < length; i++){
      v[i] = a;
    }
  }
}

// Overloaded operators

double& Vector::operator[](int i) // Return v[i]
{
  // No bounds checking
  return v[i];
}


double Vector::operator[](int i) const // Return by value
{
  // No bounds checking
  return v[i];
}


double Vector::operator()(int i) const // Return by value
{
  // No bounds checking
  return v[i];
}


Vector& Vector::operator=(const Vector& u)
{
  int newsize = u.size(); // Get the size
  resize(newsize); // Resize the vector
  // Copy in the values from u
  for (int i = 0; i < newsize; i++){
    v[i] = u.v[i];
  } 
  return *this;
}

// Unary operators

Vector Vector::operator+() const
{
  Vector rvec(n); // Make a vector of size n to return
  for(int i = 0; i < n; i++) { //copy in the values
    rvec[i] = v[i];
  }
  return rvec;
}


Vector Vector::operator-() const
{
  Vector rvec(n); 
  for (int i = 0; i<n; i++) {
    rvec[i] = -v[i];
  }
  return rvec;
}

// Binary operators - will work for vectors of diff. sizes, but throw a warning

Vector Vector::operator+(const Vector& u) const
{
  int size = u.size();
  size = ( n < size ? n : size ); // Set size to the smaller of the vector sizes
  // If different, warn the user, but carry on
  if(size != n) { 
    throw( Error("WARNING", "Vectors are different sizes.") );
  }
  Vector rvec(size); // If one vector is bigger, excess is lost
  for (int i = 0; i < size; i++) { // Do the addition
    rvec[i] = v[i]+u.v[i];
  }
  return rvec;
}


Vector Vector::operator-(const Vector& u) const
{
  int size = u.size();
  size = ( n < size ? n : size ); 
  // If different, warn the user, but carry on                           
  if(size != n) { 
    throw(Error("WARNING", "Vectors are different sizes."));
  } 
  Vector rvec(size); 
  for (int i = 0; i < size; i++) { // Subtract 
    rvec[i] = v[i]-u.v[i]; // This is a left-to-right operator
   }
  return rvec;
}

// Intrinsic functions

// Pretty print
void Vector::print(double PRECISION) const 
{
  double val = 0.0; // Temp printing float, to avoid tiny, tiny numbers
  for (int i = 0; i < n; i++){
    if (v[i] > PRECISION){
      val = v[i];
    }
    std::cout << std::setprecision(18) << std::setw(25) << val;
  }
  std::cout << "\n";
}

// Friend functions
// Inner (dot) product of two vectors
double inner(const Vector& u, const Vector& w)
{
  double rVal = 0.0; // Return value
  // Get lengths of vectors, check they match
  int usize = u.size();
  int wsize = w.size();
  if(usize == wsize){
    // Calculate inner product
    for (int i = 0; i < usize; i++){
      rVal += u(i)*w(i); // Round brackets return by value, not reference
    }
  } else { // Throw error, and return null vector
    throw( Error("VECDOT", "Vectors different sizes.") );
  }
  return rVal;
}

// Calculate p-norm of vector u.
// Default to 2-norm, p should be greater than or equal to 0, but no check is given.
// p=0 will give the infinity norm as there isn't an appropriate symbol for infinity
// (and a 0-norm would be pointless).
double pnorm(const Vector& u, int p) 
{
  int usize = u.size();
  double rVal = 0.0; // Initialise return value
  // Check if infinity norm
  if (p == 0){
    // Find the maximum element
    for (int i = 0; i < usize; i++){
      rVal = (u(i) > rVal ? u(i) : rVal);
    }
  } else {
    for (int i = 0; i < usize; i++) {
      // Calculate (p-norm)^p
      rVal += std::pow(u(i), p);   
    }
    rVal = std::pow(rVal, 1.0/(double(p)));
  }
  return rVal;
}

// Get the angle between two vectors
double angle(const Vector& u, const Vector& w)
{
  // Get the magnitudes of the vectors
  double unorm = pnorm(u);
  double wnorm = pnorm(w);
  // Get the dot product
  double dprod = inner(u, w);
  // Use the cosine rule
  // but make sure neither is a zero vector
  double rval = 0.0;
  if(dprod > 1E-12){
    rval = std::acos(dprod/(unorm*wnorm));
  }
  return rval;
}
