/*
 *   Implementation of vector.hpp
 *
 *   DATE               AUTHOR                  CHANGES
 *   ============================================================================
 *   14/08/15           Robert Shaw             Original code.
 *   15/08/15           Robert Shaw             Added error handling.
 *
 */
 
 #include "matrix.hpp"
 #include "vector.hpp"
 #include "error.hpp"

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
