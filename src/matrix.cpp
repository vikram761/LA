#include "matrix.hpp"
#include <stdexcept>
#include <math.h>

/* Returns number of rows */
size_t Matrix::row_count() {
  return matrix_a.size();
};

/* Returns number of columns */
size_t Matrix::col_count(){
  return matrix_a[0].size();
};


/*
 * Returns a new matrix which is the result of matrix addition
 */
Matrix Matrix::operator+(Matrix& matrix_b){
  size_t row1 = matrix_a.size(), col1 = matrix_a[0].size();
  size_t row2 = matrix_b.row_count(), col2 = matrix_b.col_count();
  
  if(row1 != row2 || col1 != col2) throw std::invalid_argument("Matrices dimentions must match");
  Matrix matrix_c(row1, col1);
  
  for(size_t i =0;i < row1;i++)
    matrix_c[i] = matrix_a[i] + matrix_b[i];

  return matrix_c;
};


/*
 * Returns a new matrix which is the result of matrix addition
 */
Matrix Matrix::operator-(Matrix& matrix_b){
  size_t row1 = matrix_a.size(), col1 = matrix_a[0].size();
  size_t row2 = matrix_b.row_count(), col2 = matrix_b.col_count();
  
  if(row1 != row2 || col1 != col2) throw std::invalid_argument("Matrices dimentions must match");
  Matrix matrix_c(row1, col1);
  
  for(size_t i =0;i < row1;i++)
    matrix_c[i] = matrix_a[i] - matrix_b[i];

  return matrix_c;
};


/*
 * Returns a new matrix which is the result of matrix multiplication
 */
Matrix Matrix::operator*(Matrix& matrix_b){
  size_t row1 = matrix_a.size(), col1 = matrix_a[0].size();
  size_t row2 = matrix_b.row_count(), col2 = matrix_b.col_count();

  if(col1 != row2) throw std::invalid_argument("Matrices dimentions doesn't match for matrix multiplication");

  Matrix matrix_c(row1, col2);

  for(size_t i = 0; i < row1; i++)
    
    for(size_t j =0; j < col2; j++)
      for(size_t k = 0; k < row2; k++)
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];

  return matrix_c;
};


/*
 * Returns a new matrix which is the result of matrix scalar multiplication
 */
Matrix Matrix::operator*(const double &k) {
  Matrix matrix_b = matrix_a;
  size_t size = matrix_a.size();

  for(size_t idx = 0;idx < size; idx++)
    matrix_b[idx] = matrix_b[idx] * k;

  return matrix_b;
};


/*
 * Returns a new matrix which is the result of matrix scalar division 
 */
Matrix Matrix::operator/(const double &k) {
  Matrix matrix_b = matrix_a;
  size_t size = matrix_a.size();

  for(size_t idx = 0;idx < size; idx++)
    matrix_b[idx] = matrix_b[idx] / k;

  return matrix_b;
};
/* 
 * Returns a boolean based on the equivalence of matrices
 */
bool Matrix::operator==(Matrix &matrix_b){
  size_t row1 = matrix_a.size(), col1 = matrix_a[0].size();
  size_t row2 = matrix_b.row_count(), col2 = matrix_b.col_count();
  
  if(row1 != row2 || col1 != col2) return false;

  for(size_t i = 0;i < row1; i++)
    for(size_t j =0;j < col1; j++)
      if(matrix_a[i][j] != matrix_b[i][j]) return false;

  return true;
}


/*
 * Matrix multiplication with a vector
 */
Vector Matrix::operator*(Vector& vector_a){
  size_t row_size = matrix_a.size(), col_size = matrix_a[0].size();
  size_t size = vector_a.size();

  if(size != col_size)
    throw std::invalid_argument("vector dimention doesn't match the matrices dimentions");

  Vector vector_b(size);
  for(size_t i =0;i < row_size; i++)
    for(size_t j =0;j < col_size; j++)
      vector_b[i] += matrix_a[i][j] * vector_a[j];

  return vector_b;
};


/*
 * Returns the matrix to its transpose
 */
Matrix Matrix::transpose(){
  size_t row_size = matrix_a.size(), col_size = matrix_a[0].size();

  Matrix result(col_size, row_size);
  for(size_t  i= 0;i < row_size; i++)
    for(size_t j =0;j < col_size; j++)
      result[j][i] = matrix_a[i][j];

  return result;
};


/*
 * Coverts the matrix to its corresponding transpose
 */
void Matrix::self_transpose() {
  size_t row_size = matrix_a.size(), col_size = matrix_a[0].size();
  
  std::vector<Vector> result = std::vector(col_size, Vector(row_size));
  for(size_t  i= 0;i < row_size; i++)
    for(size_t j =0;j < col_size; j++)
      result[j][i] = matrix_a[i][j];

  matrix_a = result;
};


/*
 * Compute the determinant of the matrix
 */
double Matrix::determinant(){
  size_t row_size = matrix_a.size(), col_size = matrix_a[0].size();

  Matrix temp = matrix_a;

  double result = 1.0;

  if(row_size != col_size) throw std::invalid_argument("Matrix must have same number of rows and columns ");
  
  for(size_t i = 0;i < row_size -1; i++){
    size_t row = i;

    double max_column_val = std::fabs(temp[i][i]);

    for(size_t k = i + 1; k < row_size ; k++){
      double val = std::fabs(temp[k][i]);
      if(val > max_column_val){
        row = k;
        max_column_val = val;
      }
    }

    if(row != i){
      std::swap(temp[row], temp[i]);
      result = -result;
    }

    if(std::fabs(temp[row][row]) < THRESHOLD) return 0.0;

    for(size_t k = i +1; k < row_size; k++){
      double multiple = temp[k][i] / temp[i][i] ;
      Vector sub = temp[i] * multiple;
      temp[k] = temp[k] - sub;
    }

    result *= temp[i][i];
  }
  
  result *= temp[row_size - 1][col_size - 1];
  return result;
};

std::vector<Vector> compute_inverse(std::vector<Vector> &matrix_a){
  size_t row_size = matrix_a.size(), col_size = matrix_a[0].size();
  if(row_size != col_size) throw std::invalid_argument("Matrix must be square in order to be invertible");
  size_t new_col_size = 2 * col_size;

  Matrix augmented(row_size, new_col_size);

  for(size_t i = 0;i < row_size; i++){
    for(size_t j =0;j < col_size; j++)
      augmented[i][j] = matrix_a[i][j];
    augmented[i][i + col_size] = 1;
  }
  
  for(size_t i =0;i < row_size ; i++) {
    size_t pivot_row = i;
    
    double max_col_val = std::fabs(augmented[i][i]);
    for(size_t k = i + 1;k < row_size; k++){
      double val = std::fabs(augmented[k][i]);
      if(val > max_col_val){
        pivot_row = k;
        max_col_val = val;
      }
    }

    if(pivot_row != i) std::swap(augmented[pivot_row], augmented[i]);

    double pivot = augmented[i][i];
    if(std::fabs(pivot) < THRESHOLD) throw std::runtime_error("Matrix is singular and cannot be inverted");
  
    augmented[i] = augmented[i] / pivot;

    for(int k =0;k < row_size; k++){
      if(k == i) continue;
      
      double factor = augmented[k][i];
      Vector sub = augmented[i] * factor;
      augmented[k] = augmented[k] - sub;
    }
  }

  std::vector<Vector> inverse(row_size, Vector(col_size));

  for(size_t i =0;i < row_size; i++)
    for(size_t j =0;j < col_size; j++)
      inverse[i][j] = augmented[i][j + col_size];

  return inverse;
};

/*
 * Returns the inverse matrix if exists
 */
Matrix Matrix::inverse(){
  Matrix result(compute_inverse(matrix_a));
  return result;
};

void Matrix::self_inverse(){
  matrix_a = compute_inverse(matrix_a);
}


