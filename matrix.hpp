/*
 *     PURPOSE: defines and implements class Matrix, a matrix with members
 *              of any class T that has defined upon it the usual
 *              arithemetic operations.
 *
 *     DATE             AUTHOR                CHANGES
 *     =====================================================================
 *     13/08/15         Robert Shaw           Original code
 *     14/08/15         Robert Shaw           Added error throwing
 */

#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

#include "vector.hpp"
#include "error.hpp"

template <class T>
class Matrix
{
private:
  int rows, cols; // No. of rows and columns of the matrix
  T** arr; // 2D array of matrix entries
  void cleanUp(); // Utility function for memory deallocation
public:
  // Constructors and destructor
  Matrix() : rows(0), cols(0), arr(NULL) {} // Default, forms zero length vector
  Matrix(int m, int n); // Declare an m x n matrix
  Matrix(int m, int n, const T& a); // Declare m x n matrix, all entries = a
  Matrix(int m, int n, const T* a); // Matrix of m row copies of n-vector a
  Matrix(const Matrix& other); // Copy constructor
  ~Matrix(); // Destructor
  // Accessors
  int nrows() const { return rows; } // Returns no. of rows
  int ncols() const { return cols; } // Returns no. of cols  
  // Shaping functions
  void resize(int m, int n); // Resize to empty m x n matrix
  void assign(int m, int n, const T& a); // Resize, setting all entries to a
  // Overloaded operators
  T& operator[](int i); // Return pointer to first element of row i
  T& operator()(int i, int j); // Return pointer to element ij
  T operator()(int i, int j) const; // Return by value element ij
  Matrix& operator=(const Matrix& other); 
  // Unary operators
  Matrix operator+() const; 
  Matrix operator-() const;
  // Binary operators
  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const T& scalar) const; // Scalar multiplication
  Matrix operator*(const Matrix& other) const; // Matrix x matrix
  // Intrinsic functions
  Matrix transpose() const; // Return the transpose of the matrix
  // Make T available externally
  typedef T value_type;
};

// Clean up utility for memory deallocation
template <class T>
void Matrix<T>::cleanUp()
{
  // No memory to deallocate if the matrix is null
  if(rows > 0){
    if(cols > 0){
      // Delete columns
      for (int i = 0; i < rows; i++){
	delete[] arr[i];
      }
    }
    // Delete rows
    delete[] arr;
  }
}

// Constructors and destructor
template <class T>
Matrix<T>::Matrix(int m, int n)
{
  // Set no. of rows and columns
  rows = m;
  cols = n;
  // Allocate memory
  if (m > 0) {
    // Start with rows
    arr = new T* [m];
    // then columns
    for (int i = 0; i < m; i++){
      if (n > 0) {
	arr[i] = new T[n];
      } else {
	arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}


// Same again, but initialise all elements to a
template <class T>
Matrix<T>::Matrix(int m, int n, const T& a)
{
  // Set no. of rows and columns                            
  rows = m;
  cols = n;
  // Allocate memory                                                                         
  if (m> 0) {
    // Start with rows                                                               
    arr = new T* [m];
    // then columns                                                               
    for(int i = 0; i < m; i++){
      if (n > 0) {
	arr[i] = new T[n];
	// Set elements to a
	for (int j = 0; j < n; j++) {
	  arr[i][j] = a;
	}
      } else {
        arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}

// Same again, but now initialise all rows to a given vector, a
template <class T>
Matrix<T>::Matrix(int m, int n, const T* a)
{
  // Set no. of rows and columns                      
  rows = m;
  cols = n;
  // Allocate memory                                                   
  if (m> 0) {
    // Start with rows                                                          
    arr = new T* [m];
    // then columns                                                                 
    for(int i = 0; i <m; i++){
      if (n > 0) {
	arr[i] = new T[n];
	// Set elements - hope a is length n!
	for (int j = 0; j < n; j++){
	  arr[i][j] = a[j];
	}
      } else {
        arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}

// Copy constructor
template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
  // Set size
  rows = other.nrows();
  cols = other.ncols();
  if (rows > 0) {
    // Allocate memory for rows
    arr = new T* [rows];
    for (int i = 0; i < rows; i++){
      if (cols > 0){
	// Allocate memory for cols
	arr[i] = new T[cols];
	// Copy in values
	for (int j = 0; j < cols; j++){
	  arr[i][j] = other.arr[i][j];
	} 
      } else {
	arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}

// Destructor
template <class T>
Matrix<T>::~Matrix()
{
  // Deallocate memory if necessary
  cleanUp();
}

// Shaping functions

// Resize to an empty m x n matrix
template <class T>
void Matrix<T>::resize(int m, int n)
{
  // Deallocate old memory if necessary
  cleanUp();
  // Set size
  rows = m;
  cols = n;
  // Reallocate memory
  if (m> 0) {
    // Start with rows                                                       
    arr = new T* [m];
    // then columns                                                  
    for(int i = 0; i <m; i++){
      if (n > 0) {
	arr[i] = new T[n];
      } else {
        arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}

// Do the above, but setting every element to a
template <class T>
void Matrix<T>::assign(int m, int n, const T& a)
{
  //Do the resizing
  resize(m, n);
  //Assign the values
  if ( m > 0 && n > 0 ) {
    for(int i = 0; i < m; i++){
      for(int j = 0; j < n; j++){
	arr[i][j] = a;
      }
    }
  }
}

// Overloaded operators

// Return pointer to first element of row i
template <class T>
T& Matrix<T>::operator[](int i)
{
  // No bounds checking
  return arr[i];
}

// Return pointer to element ij
template <class T>
T& Matrix<T>::operator()(int i, int j)
{
  // No bounds checking
  return arr[i][j];
}

// Return by value
template <class T>
T Matrix<T>::operator()(int i, int j) const
{
  // No bounds checking
  return arr[i][j];
}

// Overload assignment operator
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
  // Get the size of other
  int newNRows = other.nrows();
  int newNCols = other.ncols();
  // Resize the matrix
  resize(newNRows, newNCols);
  // Copy in the values from other
  for (int i = 0; i < newNRows; i++){
    for (int j = 0; j < newNCols; j++){
      arr[i][j] = other.arr[i][j];
    }
  }
  return *this;
}

// Unary operators
template <class T>
Matrix<T> Matrix<T>::operator+() const
{
  Matrix<T> rMat(rows, cols); // Create correct sized return matrix
  // Copy in values
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      rMat(i, j) = arr[i][j];
    }
  }
  return rMat;
}

template <class T>
Matrix<T> Matrix<T>::operator-() const
{
  Matrix<T> rMat(rows, cols);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      rMat(i, j) = -arr[i][j];
    }
  }
  return rMat;
}

// Binary operators - will work for different shaped matrices, but will throw a warning
template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
  // Get shape of other
  int oRows = other.nrows();
  int oCols = other.ncols();
  // Find the smaller of each matrix dimension
  int rowsize = (rows < oRows ? rows : oRows);
  int colsize = (cols < oCols ? cols : oCols);
  // Throw a warning if there is a size mismatch, but continue anyway
  if (rows != rowsize || cols != colsize){
    throw(Error("WARNING", "Matrices are different sizes.")); 
  }
  // Make return matrix and add together elementwise
  Matrix<T> rMat(rowsize, colsize);
  for (int i = 0; i < rowsize; i++){
    for (int j = 0; j < colsize; j++){
      rMat(i, j) = arr[i][j] + other.arr[i][j];
    }
  }
  return rMat;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const
{
  // Get shape of other                                                  
  int oRows = other.nrows();
  int oCols = other.ncols();
  // Find the smaller of each matrix dimension                                   
  int rowsize = (rows < oRows ? rows : oRows);
  int colsize = (cols < oCols ? cols : oCols);
  // Throw a warning if there is a size mismatch, but continue anyway                 
  if (rows != rowsize || cols != colsize){
    throw(Error("WARNING", "Matrices are different sizes."));
  }
  // Make return matrix and add together elementwise                                      
  Matrix<T> rMat(rowsize, colsize);
  for (int i = 0; i < rowsize; i++){
    for (int j = 0; j < colsize; j++){
      rMat(i, j) = arr[i][j] - other.arr[i][j]; // Left to right operator
    }
  }
  return rMat;
}

// Scalar multiplication
template <class T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const
{
  // Make return matrix of correct size
  Matrix<T> rMat(rows, cols);
  // Multiply elements by scalar
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      rMat(i, j) *= arr[i][j]*scalar;
    }
  }
  return rMat;
}

// Matrix multiplication - will throw error if incompatible sizes, returning an empty matrix
template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
  int oRows = other.nrows();
  int oCols = other.ncols();
  // Make return matrix of correct size
  // Left to right operator implies has shape (rows x oCols)
  Matrix<T> rMat(rows, oCols);
  // Throw error if incompatible, leaving rMat empty
  if (cols != oRows){
    throw(Error("MATMULT", "Matrices are incompatible sizes for multiplication."));
  } else {
    // Multiply them
    for (int i = 0; i < rows; i++){
      for (int j = 0; j < oCols; j++){
	for (int k = 0; k < cols; k++){
	  rMat(i, j) += arr[i][k]*other.arr[k][j];
	}
      }
    }
  }
  return rMat;
}

// Intrinsic functions

// Return the transpose of the matrix
template <class T>
Matrix<T> Matrix<T>::transpose() const
{
  Matrix<T> rMat(cols, rows); // Make return vector with rows and cols interchanged
  // Set elements
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      rMat(j, i) = arr[i][j];
    }
  }
  return rMat;
}

// Define some standard matrix types
typedef Matrix<int> iMatrix; // Matrix of integers
typedef Matrix<double> dMatrix; // Matrix of double precision floats

#endif
