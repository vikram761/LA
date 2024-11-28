#include "matrix.hpp"
#include <stdexcept>

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
}
