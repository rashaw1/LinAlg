/*
 *   Implementation of matrix.hpp
 *
 *   DATE               AUTHOR                  CHANGES
 *   ============================================================================
 *   14/08/15           Robert Shaw             Original code.
 *   15/08/15           Robert Shaw             Added error handling.
 *
 */
 
 #include "matrix.hpp"
 #include "vector.hpp"
#include <cmath>
 
// Clean up utility for memory deallocation

void Matrix::cleanUp()
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

Matrix::Matrix(int m, int n)
{
  // Set no. of rows and columns
  rows = m;
  cols = n;
  // Allocate memory
  if (m > 0) {
    // Start with rows
    arr = new double* [m];
    // then columns
    for (int i = 0; i < m; i++){
      if (n > 0) {
	arr[i] = new double[n];
      } else {
	arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}


// Same again, but initialise all elements to a

Matrix::Matrix(int m, int n, const double& a)
{
  // Set no. of rows and columns                            
  rows = m;
  cols = n;
  // Allocate memory                                                                         
  if (m> 0) {
    // Start with rows                                                               
    arr = new double* [m];
    // then columns                                                               
    for(int i = 0; i < m; i++){
      if (n > 0) {
	arr[i] = new double[n];
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

Matrix::Matrix(int m, int n, const double* a)
{
  // Set no. of rows and columns                      
  rows = m;
  cols = n;
  // Allocate memory                                                   
  if (m> 0) {
    // Start with rows                                                          
    arr = new double* [m];
    // then columns                                                                 
    for(int i = 0; i <m; i++){
      if (n > 0) {
	arr[i] = new double[n];
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

Matrix::Matrix(const Matrix& other)
{
  // Set size
  rows = other.nrows();
  cols = other.ncols();
  if (rows > 0) {
    // Allocate memory for rows
    arr = new double* [rows];
    for (int i = 0; i < rows; i++){
      if (cols > 0){
	// Allocate memory for cols
	arr[i] = new double[cols];
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

Matrix::~Matrix()
{
  // Deallocate memory if necessary
  cleanUp();
}

// Accessors
// Get a row or column of the matrix as a vector
Vector Matrix::rowAsVector(int r) const
{
  // No bounds checking
  Vector rVec(cols); // Create a vector with dimension 'cols'
  // Copy in the values from row r
  for (int i = 0; i < cols; i++){
    rVec[i] = arr[r][i];
  }
  return rVec;
}

Vector Matrix::colAsVector(int c) const
{
  // No bounds checking
  Vector rVec(rows);
  for (int i = 0; i < rows; i++){
    rVec[i] = arr[i][c];
  }
  return rVec;
}

// Set a row or column by a vector
void Matrix::setRow(int r, const Vector& u)
{
  // No bounds checking
  int size = u.size();
  // Determine whether u or the width of matrix
  // is smaller
  size = (cols < size ? cols : size); 
  // If not the same, throw an error!
  if ( size != cols ) {
    throw( Error("SETROW", "Vector and matrix are different sizes.") );
  }
  // Proceed anyway, as far as possible
  for (int i = 0; i < size; i++){
    arr[r][i] = u(i);
  }
}

void Matrix::setCol(int c, const Vector& u)
{
  int size = u.size();
  size = (rows < size ? rows : size);
  if ( size != rows ) {
    throw( Error("SETCOL", "Vector and matrix are different sizes.") );
  }
  for (int i = 0; i < size; i++ ){
    arr[i][c] = u(i);
  }
}
  
// Shaping functions

// Resize to an empty m x n matrix

void Matrix::resize(int m, int n)
{
  // Deallocate old memory if necessary
  cleanUp();
  // Set size
  rows = m;
  cols = n;
  // Reallocate memory
  if (m> 0) {
    // Start with rows                                                       
    arr = new double* [m];
    // then columns                                                  
    for(int i = 0; i <m; i++){
      if (n > 0) {
	arr[i] = new double[n];
      } else {
        arr[i] = NULL;
      }
    }
  } else {
    arr = NULL;
  }
}

// Do the above, but setting every element to a

void Matrix::assign(int m, int n, const double& a)
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

double& Matrix::operator[](int i)
{
  // No bounds checking
  return arr[i][0];
}

// Return pointer to element ij

double& Matrix::operator()(int i, int j)
{
  // No bounds checking
  return arr[i][j];
}

// Return by value

double Matrix::operator()(int i, int j) const
{
  // No bounds checking
  return arr[i][j];
}

// Overload assignment operator

Matrix& Matrix::operator=(const Matrix& other)
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

Matrix Matrix::operator+() const
{
  Matrix rMat(rows, cols); // Create correct sized return matrix
  // Copy in values
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      rMat(i, j) = arr[i][j];
    }
  }
  return rMat;
}


Matrix Matrix::operator-() const
{
  Matrix rMat(rows, cols);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      rMat(i, j) = -arr[i][j];
    }
  }
  return rMat;
}

// Binary operators - will work for different shaped matrices, but will throw a warning

Matrix Matrix::operator+(const Matrix& other) const
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
  Matrix rMat(rowsize, colsize);
  for (int i = 0; i < rowsize; i++){
    for (int j = 0; j < colsize; j++){
      rMat(i, j) = arr[i][j] + other.arr[i][j];
    }
  }
  return rMat;
}


Matrix Matrix::operator-(const Matrix& other) const
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
  Matrix rMat(rowsize, colsize);
  for (int i = 0; i < rowsize; i++){
    for (int j = 0; j < colsize; j++){
      rMat(i, j) = arr[i][j] - other.arr[i][j]; // Left to right operator
    }
  }
  return rMat;
}

// Matrix multiplication - will throw error if incompatible sizes, returning an empty matrix

Matrix Matrix::operator*(const Matrix& other) const
{
  int oRows = other.nrows();
  int oCols = other.ncols();
  // Make return matrix of correct size
  // Left to right operator implies has shape (rows x oCols)
  Matrix rMat(rows, oCols);
  // Throw error if incompatible, leaving rMat empty
  if (cols != oRows){
    throw(Error("MATMULT", "Matrices are incompatible sizes for multiplication."));
  } else {
    // Multiply them
    Vector lhs(cols); // Store each vector on left hand side
    Vector rhs(oRows); // Store each vector on right hand side
    for (int i = 0; i < rows; i++){
      lhs = rowAsVector(i);
      for (int j = 0; j < oCols; j++){
	rhs = other.colAsVector(j);
	rMat(i, j) = inner(lhs, rhs); // Take dot product
      }
    }
  }
  return rMat;
}

// Intrinsic functions

// Return the transpose of the matrix

Matrix Matrix::transpose() const
{
  Matrix rMat(cols, rows); // Make return vector with rows and cols interchanged
  // Set elements
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      rMat(j, i) = arr[i][j];
    }
  }
  return rMat;
}

// Pretty print
void Matrix::print() const
{
  // Prints vectors by row
  Vector temp(cols);
  for (int i = 0; i < rows; i++) {
    temp = rowAsVector(i);
    temp.print();
  }
}

// Friend functions

// Calculate the induced matrix p-norm 
// note that, like with vectors, the infinity norm is p=0
double pnorm(const Matrix& m, int p)
{
  double rval = 0.0; // Return value
  // Get number of rows and cols in m
  int cols = m.ncols();  
  int rows = m.nrows();
  // Switch p, as each norm is different! (unlike with vectors)
  switch(p){
  case 0: // The induced infinity norm is the maximum row sum
    {  Vector temp1(cols); // Make a temporary vector to store each row
    double tval1; // Temporary norm value
    for (int i = 0; i < rows; i++) { // Loop over rows
      temp1 = m.rowAsVector(i);
      tval1 = pnorm(temp1, 1); // Get 1-norm (i.e. sum of values)
      // Change rval if tval is bigger
      rval = (tval1 > rval ? tval1 : rval);
    }
    }
    break;
  case 1: // The induced 1-norm is the maximum col sum
    {Vector temp2(rows);
    double tval2;
    for (int i = 0; i < cols; i++) {
      temp2 = m.colAsVector(i);
      tval2 = pnorm(temp2, 1);
      rval = (tval2 > rval ? tval2 : rval);
    }
    }
    break;
  case 2:
    break;
  default:
    rval = 0.0;
  }
  return rval;
}

// Return the Frobenius norm of the matrix m, the root sum of squares
// of all the elements of m. Alternatively, the root of the sum of the
// 2-norm of each column/row vector, or the root of the trace of
// the product of m with its adjugate.
double fnorm(const Matrix& m)
{
  double rval = 0.0;
  // Sum the squares 
  for (int i = 0; i < m.nrows(); i++) {
    for (int j = 0; j < m.ncols(); j++) {
      rval += m(i, j) * m(i, j);
    }
  }
  // Square root
  rval = std::sqrt(rval);
  return rval;
}

    
  
