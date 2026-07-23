#include "collision-detection/collision-area.hpp"

#include <algorithm>
#include <cmath>
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
  // CollisionArea solid(Point<2>(0, 0),
  //                     {
  //                         Segment<2>(Point<2>(20, 20), Point<2>(30, 20)),
  //                         Segment<2>(Point<2>(20, 20), Point<2>(30, 28)),
  //                         Segment<2>(Point<2>(20, 20), Point<2>(20, 30)),
  //                         Segment<2>(Point<2>(20, 20), Point<2>(30, 15)),
  //                         Segment<2>(Point<2>(20, 20), Point<2>(30, 10)),
  //                         Segment<2>(Point<2>(20, 20), Point<2>(20, 10)),
  //                         Segment<2>({20, 20}, {18, 15}),
  //                         Segment<2>({20, 20}, {10, 10}),
  //                         Segment<2>({20, 20}, {5, 10}),
  //                         Segment<2>({20, 20}, {10, 20}),
  //                         Segment<2>({20, 20}, {12, 23}),
  //                         Segment<2>({20, 20}, {15, 25}),
  //                     });
  // CollisionArea solid(Point<2>(0, 0),
  //                     {
  //                         Parallelogram<2>({0, 0}, {4, 0}, {7, 10}, {3, 10}),
  //                         Parallelogram<2>({4, 0}, {0, 3}, {3, 10}, {7, 7}),
  //                     });
  CollisionArea solid(Point<2>(0, 0), {Circle<2>(Point<2>(20, 20), 10)});
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
