#pragma once

#include <vector.hpp>
#include <vector>

static double THRESHOLD = 1.0e-30;

class Matrix {
private:
  std::vector<Vector> matrix_a;
  Matrix(const std::vector<std::vector<double>> &elems) {
    size_t rows = elems.size();
    size_t cols = elems[0].size();

    matrix_a = std::vector<Vector>(rows, Vector(cols));

    for (size_t i = 0; i < rows; i++) {
      Vector temp(elems[i]);
      matrix_a[i] = temp;
    }
  };

public:
  Matrix(size_t rows, size_t cols) : matrix_a(rows, Vector(cols)) {};
  Matrix(size_t rows, size_t cols, double val)
      : matrix_a(rows, Vector(cols, val)) {};
  Matrix(const std::vector<Vector> &elems) : matrix_a(elems) {};

  /*
   * Constructor to convert vector of vector of double
   * to a matrix which consist of vector of Vectors
   */
  Matrix(std::initializer_list<std::vector<double>> elems)
      : Matrix(std::vector<std::vector<double>>(elems)) {}

  size_t row_count();
  size_t col_count();

  Matrix transpose();
  void self_transpose();

  double determinant();

  /* OPERATORS */
  Vector &operator[](size_t idx) { return matrix_a.at(idx); };
  const Vector &operator[](size_t idx) const { return matrix_a.at(idx); };

  Matrix operator+(Matrix &matrix_b);
  Matrix operator-(Matrix &matrix_b);
  Matrix operator*(Matrix &matrix_b);
  Matrix operator*(const double &k);
  Vector operator*(Vector &vector);
};
