#include "vector.hpp"
#include <stdexcept>

/*
 * Returns the size of the vector
 */
size_t Vector::size() { return vector_a.size(); };

/*
 * Returns a new vector with vector addition
 */
Vector Vector::operator+(Vector vector_b) {
  size_t a_size = vector_a.size();
  size_t b_size = vector_b.size();

  if (a_size != b_size)
    throw std::invalid_argument("Vector size must match");

  Vector vector_c(a_size);
  for (size_t idx = 0; idx < a_size; idx++)
    vector_c[idx] = vector_a[idx] + vector_b[idx];

  return vector_c;
};


/*
 * Returns a new vector with vector subraction 
 */
Vector Vector::operator-(Vector vector_b) {
  size_t a_size = vector_a.size();
  size_t b_size = vector_b.size();

  if (a_size != b_size)
    throw std::invalid_argument("Vector size must match");

  Vector vector_c(a_size);
  for (size_t idx = 0; idx < a_size; idx++)
    vector_c[idx] = vector_a[idx] - vector_b[idx];

  return vector_c;
};

/*
 * Returns a new vector with scalar multiplication
 */
Vector Vector::operator*(const double& k) {
  size_t size = vector_a.size();

  Vector vector_c(size);
  for (size_t idx = 0; idx < size; idx++) 
    vector_c[idx] = vector_a[idx] * k;

  return vector_c;
};
