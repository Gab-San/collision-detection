#ifndef _POINT_HPP
#define _POINT_HPP

template <unsigned int dim> struct Point;

template <> struct Point<2> {
  const int x;
  const int y;

  Point(int x_, int y_) : x(x_), y(y_) {}
  ~Point() = default;
};

template <> struct Point<3> {
  const int x;
  const int y;
  const int z;
  Point(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {};
};

#endif // _POINT_HPP
