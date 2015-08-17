/*
 *     PURPOSE: defines and implements class Matrix, a matrix with members
 *              of any class T that has defined upon it the usual
 *              arithemetic operations.
 *
 *     NOTE: implemented in header file due to templating - avoids some
 *           potential linking issues.
 *
 *     DATE             AUTHOR                CHANGES
 *     =====================================================================
 *     13/08/15         Robert Shaw           Original code
 *     14/08/15         Robert Shaw           Added error throwing
 */

#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF

// Forward dependencies
class Error;

class Matrix
{
	typedef double T; // Leave room for templating
private:
  int rows, cols; // No. of rows and columns of the matrix
  T** arr; // 2D array of matrix entries
  void cleanUp(); // Utility function for memory deallocation
public:
  // Constructors and destructor
  Matrix() : rows(0), cols(0) {} // Default, forms zero length vector
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
  Matrix& operator*=(const T& scalar) { return *this; } // Scalar multiplication
  Matrix operator*(const Matrix& other) const; // Matrix x matrix
  // Intrinsic functions
  Matrix transpose() const; // Return the transpose of the matrix
};

#endif
