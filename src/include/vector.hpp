#ifndef _VECTOR_HPP
#define _VECTOR_HPP

#include "point.hpp"

#include <stdexcept>

template <int dim> struct Vector {
  const Point<dim> A, B;

  Vector(const Point<dim> &A_, const Point<dim> &B_) : A(A_), B(B_) {}

  const int dot(const Vector<dim> &other) const {
    if constexpr (dim == 2) {
      return (B - A).x * (other.B - other.A).x +
             (B - A).y * (other.B - other.A).y;
    } else {
      std::runtime_error("Vector<3>::dot() : dim == 3 not implemented");
    }
  }
};

// template <> struct Vector<2> {
//   const Point<2>
// };

#endif // _VECTOR_HPP
