// PURPOSE: defines and implements class Vector, a vector with members 
//          of any class T, which has defined upon it the usual 
//          arithemetic operations. 
//
// DATE             AUTHOR                CHANGES
// ==========================================================================
// 13/08/15         Robert Shaw           Original code
//

#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF

template <class T>
class Vector
{
private:
  int n; // The number of elements
  T* v; // The elements themselves
  void cleanUp(); // Deallocates memory
public:
  // Constructors and destructor
  Vector() : n(0), v(NULL) {} // Default constructor, zero length vector
  Vector(int length); // Empty vector of length length
  Vector(int length, const T& a); // Vector with 'length' values, all a
  Vector(int length, const T* a); // Initialise vector to array a
  Vector(const Vector& u); // Copy constructor
  ~Vector(); // Destructor
  // Accessors
  int size() const { return n; } // Returns size of vector, n
  // Shaping functions
  void resize(int length); // Resizes the vector to length 'length',
                           // without preserving values
  void resizeCopy(int length); // Resizes and preserves values up to length
  void assign(int length, const T& a); // Resizes and sets elements to a
  // Overloaded operators
  T& operator[](int i); // Access value at index i
  Vector& operator=(const Vector& u); // Set this = u
  // Unary operators
  Vector operator+() const; 
  Vector operator-() const;
  // Binary operators
  Vector operator+(const Vector& u) const;
  Vector operator-(const Vector& u) const;
  Vector operator*(const T& scalar) const; // Scalar multiplication
  // Typedefs
  typedef T value_type;  
};

// Memory clean up function
template <class T>
void Vector<T>::cleanUp()
{
  // if n = 0, no memory was ever allocated!
  if ( size() > 0 ) {
    delete[] v;
  }
}

// Constructors
template <class T>
Vector<T>::Vector(int length)
{
  n = length; // Set length of vector
  if(length > 0){ // Allocate memory
    v = new T[length];
  } else {
    v = NULL;
  }
}

template <class T>
Vector<T>::Vector(int length, const T& a)
{
  n = length; // Set length of vector
  if(length > 0){ // Allocate memory and set all values to a
    v = new T[length];
    for(int i=0; i<length; i++){
      v[i] = a;
    }
  } else {
    v = NULL;
  }
}

template <class T>
Vector<T>::Vector(int length, const T* a)
{
  n = length; // Set length
  if (length > 0) { // Allocate memory, and copy a into vector
    v = new T[length];
    for(int i = 0; i < length; i++){
      v[i] = a[i]; // Really hope that a is the right length!
    }
  } else {
    v = NULL;
  }
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector& u)
{
  n = u.size(); // Get size
  if(n > 0) { // Allocate size, and copy in values
    v = new T[n];
    for (int i = 0; i < n; i++) {
      v[i] = u.v[i];
    }
  } else {
    v = NULL;
  }
}

// Destructor
template <class T>
Vector<T>::~Vector()
{
  cleanUp(); // Deallocate memory if necessary
}

// Shaping functions
template <class T>
void Vector<T>::resize(int length) // Resize with loss of values
{
  cleanUp(); // Deallocate old memory
  n = length; // Reset size
  if (length > 0) { // Reallocate memory
    v = new T[length];
  } else {
    v = NULL;
  }
}

template <class T>
void Vector<T>::resizeCopy(int length) { 
  // Resizes, keeping as many values as fit
  T* tempV;
  if ( n > 0 ) {
    tempV = new T[n]; // Store old values
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

template <class T>
void Vector<T>::assign(int length, const T& a) // Resizes, setting all vals to a
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
template <class T>
T& Vector<T>::operator[](int i) // Return v[i]
{
  // No bounds checking
  return v[i];
}


template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& u)
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
template <class T>
Vector<T> Vector<T>::operator+() const
{
  Vector<T> rvec(n); // Make a vector of size n to return
  for(int i = 0; i < n; i++) { //copy in the values
    rvec[i] = v[i];
  }
  return rvec;
}

template <class T>
Vector<T> Vector<T>::operator-() const
{
  Vector<T> rvec(n); 
  for (int i = 0; i<n; i++) {
    rvec[i] = -v[i];
  }
  return rvec;
}

// Binary operators - will work for vectors of diff. sizes
template <class T>
Vector<T> Vector<T>::operator+(const Vector<T>& u) const
{
  int size = u.size();
  size = ( n < size ? n : size ); // Set size to the smaller of the vector sizes
  Vector<T> rvec(size); // If one vector is bigger, excess is lost
  for (int i = 0; i < size; i++) { // Do the addition
    rvec[i] = v[i]+u.v[i];
  }
  return rvec;
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector<T>& u) const
{
  int size = u.size();
  size = ( n < size ? n : size ); 
  Vector<T> rvec(size); 
  for (int i = 0; i < size; i++) { // Subtract 
    rvec[i] = v[i]-u.v[i]; // This is a left-to-right operator
   }
  return rvec;
}

// Scalar multiplication
template <class T>
Vector<T> Vector<T>::operator*(const T& scalar) const
{
  Vector<T> rvec(n);
  for(int i = 0; i < n; i++){
    rvec[i] = v[i]*scalar;
  }
  return rvec;
}

#endif
