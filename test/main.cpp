#include "collision-detection/collision_area.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace lbm;
using namespace lbm::CollisionDetection;
using namespace lbm::utils;

template <unsigned int dim> void draw(CollisionArea<dim> &, bool hard_contain);
template <unsigned int dim>
std::ostream &operator<<(std::ostream &out,
                         const std::vector<Point<dim>> &perimeter);

int main(int argc, char *argv[]) {

  std::vector<CollisionShapesT<2>> shapes;

  CollisionArea<2> solid(
      Point<2>(-5, -5),
      {
          Circle<2>(Point<2>(10, 10), 5),
          Segment<2>(Point<2>(20, 20), Point<2>(25, 23)),
          // Segment<2>(Point<2>(10, 15), Point<2>(15, 15)),
          // Segment<2>(Point<2>(15, 10), Point<2>(15, 15)),
          // Parallelogram<2>(Point<2>(15, 10), Point<2>(15, 15), Point<2>(10,
          // 15),
          //                  Point<2>(10, 10)),
          // Parallelogram<2>(Point<2>(30, 30), Point<2>(35, 35)),

          // Parallelogram<2>(Point<2>(24, 20), Point<2>(26, 22), Point<2>(22,
          // 26),
          //                  Point<2>(20, 24)),
          // Segment<2>(Point<2>(0, 0), Point<2>(0, 129)),
          // Segment<2>(Point<2>(0, 129), Point<2>(129, 129)),
          // Segment<2>(Point<2>(129, 129), Point<2>(129, 0))
      });
  bool hard_contain = false;
  if (argc > 1) {
    hard_contain = *argv[1] == '1';
  }

  draw(solid, hard_contain);
  draw(solid, true);

  std::cout << solid.getPerimeter() << std::endl;

  return 0;
}

#define VIEWPORT_WIDTH 40
#define VIEWPORT_HEIGHT 30

template <unsigned int dim>
void draw(CollisionArea<dim> &solid, bool hard_contain) {
  int digits = std::log10(VIEWPORT_HEIGHT) + 1;

  for (int x = 0; x < VIEWPORT_WIDTH; x++) {
    if (x == 0) {
      std::cout << VIEWPORT_WIDTH << "";
    } else {
      std::cout << "-";
    }

    if (x == VIEWPORT_WIDTH - 1) {
      std::cout << "- x" << std::endl;
    }
  }

  for (int y = 0; y < VIEWPORT_HEIGHT; y++) {
    std::cout.width(digits);
    std::cout << y << "|";
    for (int x = 0; x < VIEWPORT_WIDTH; x++) {
      if ((!hard_contain ? solid.isCollidingWith(Point<dim>(x, y))
                         : solid.contains(Point<dim>(x, y)))) {
        std::cout << "*";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < digits; i++) {
    std::cout << " ";
  }

  std::cout << "" << std::endl;
  std::cout.width(digits + 1);
  std::cout << "y" << std::endl;
};

template <unsigned int dim>
std::ostream &operator<<(std::ostream &out,
                         const std::vector<Point<dim>> &perimeter) {
  out << "[";
  for (const auto &[xp, yp] : perimeter) {
    out << "(" << xp << "," << yp << ") : ";
  }
  out << "]" << std::endl;

  int digits = std::log10(VIEWPORT_HEIGHT) + 1;

  for (int x = 0; x < VIEWPORT_WIDTH; x++) {
    if (x == 0) {
      std::cout << VIEWPORT_WIDTH << "";
    } else {
      std::cout << "-";
    }

    if (x == VIEWPORT_WIDTH - 1) {
      std::cout << "- x" << std::endl;
    }
  }

  for (int y = 0; y < VIEWPORT_HEIGHT; y++) {
    std::cout.width(digits);
    std::cout << y << "|";
    for (int x = 0; x < VIEWPORT_WIDTH; x++) {
      if (std::find(perimeter.begin(), perimeter.end(), Point<2>(x, y)) !=
          perimeter.end()) {
        std::cout << "*";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < digits; i++) {
    std::cout << " ";
  }
  std::cout << "" << std::endl;
  std::cout.width(digits + 1);
  std::cout << "y" << std::endl;
  return out;
}
