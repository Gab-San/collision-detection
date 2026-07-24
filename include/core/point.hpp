#ifndef __CORE_POINT_HPP
#define __CORE_POINT_HPP

// C++ STANDARD LIB
#include <iostream>

namespace CollisionDetection {
namespace utils {

template <typename T, unsigned int dim> struct Point;

template <typename T> struct Point<T, 2> {
  const T x, y;

  Point(const T x_, const T y_) : x(x_), y(y_) {}
  ~Point() = default;

  // ---- OPERATOR OVERLOADING ----
  inline friend bool operator==(const Point<T, 2> &lhs,
                                const Point<T, 2> &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  inline friend Point<T, 2> operator+(const Point<T, 2> &lhs,
                                      const Point<T, 2> &rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  inline friend Point<T, 2> operator-(const Point<T, 2> &lhs,
                                      const Point<T, 2> &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  inline friend std::ostream &operator<<(std::ostream &out,
                                         const Point<T, 2> &p) {
    return out << "Point(" << p.x << "," << p.y << ")";
  }
};

template <typename T> struct Point<T, 3> {
  const T x, y, z;

  Point(const T x_, const T y_, const T z_) : x(x_), y(y_), z(z_) {};
  ~Point() = default;

  // ---- OPERATOR OVERLOADING ----
  inline friend bool operator==(const Point<T, 3> &lhs,
                                const Point<T, 3> &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
  }

  inline friend Point<T, 3> operator+(const Point<T, 3> &lhs,
                                      const Point<T, 3> &rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  }

  inline friend Point<T, 3> operator-(const Point<T, 3> &lhs,
                                      const Point<T, 3> &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  }

  inline friend std::ostream &operator<<(std::ostream &out,
                                         const Point<T, 3> &p) {
    return out << "(" << p.x << "," << p.y << "," << p.z << ")";
  }
};

} // namespace utils
} // namespace CollisionDetection

#endif // __CORE_POINT_HPP
