#ifndef _POINT_HPP
#define _POINT_HPP

// C++ STANDARD LIB
#include <iostream>

namespace lbm {
namespace utils {

template <unsigned int dim> struct Point;

template <> struct Point<2> {
  const int x;
  const int y;

  Point(const int x_, const int y_) : x(x_), y(y_) {}
  ~Point() = default;

  inline const unsigned int distsqr(const Point<2> &B) const {
    return (x - B.x) * (x - B.x) + (y - B.y) * (y - B.y);
  }

  // ---- OPERATOR OVERLOADING ----

  inline friend bool operator==(const Point<2> &lhs, const Point<2> &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  inline friend Point<2> operator+(const Point<2> &lhs, const Point<2> &rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  inline friend Point<2> operator-(const Point<2> &lhs, const Point<2> &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  inline friend std::ostream &operator<<(std::ostream &out, const Point<2> &p) {
    return out << "Point(" << p.x << "," << p.y << ")";
  }
};

template <> struct Point<3> {
  const int x;
  const int y;
  const int z;
  Point(const int x_, const int y_, const int z_) : x(x_), y(y_), z(z_) {};
  ~Point() = default;

  inline friend bool operator==(const Point<3> &lhs, const Point<3> &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }

  inline friend Point<3> operator+(const Point<3> &lhs, const Point<3> &rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }

  inline friend Point<3> operator-(const Point<3> &lhs, const Point<3> &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }

  inline friend std::ostream &operator<<(std::ostream &out, const Point<3> &p) {
    return out << "(" << p.x << "," << p.y << "," << p.z << ")";
  }

  inline const unsigned int distsqr(const Point<3> &B) const {
    return (x - B.x) * (x - B.x) + (y - B.y) * (y - B.y) +
           (z - B.z) * (z - B.z);
  }
};

} // namespace utils
} // namespace lbm

#endif // _POINT_HPP
