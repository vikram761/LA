#pragma once

#include <vector>

class Vector{
  private:
    std::vector<double> vector_a;
  public:
    Vector(size_t size) : vector_a(size, 0.0) {};
    Vector(size_t size, double val) : vector_a(size, val) {};
    Vector(const std::vector<double> &elems) : vector_a(elems){};

    void print();
    size_t size();

    // OPERATORS
    double& operator[](size_t idx) { return vector_a.at(idx);}
    const double& operator[](size_t idx) const { return vector_a.at(idx);}

    Vector operator+(Vector vector_b);
    Vector operator*(const double& k);
};
