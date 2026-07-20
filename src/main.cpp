#include "point.hpp"
#include "solid.hpp"

#include <iostream>
#include <memory>

template <unsigned int dim> void draw(RigidBody<dim> &);

int main() {
  std::vector<std::unique_ptr<Shape<2>>> shapes;
  shapes.push_back(
      std::make_unique<Segment<2>>(Point<2>({0, 0}), Point<2>({0, 129})));
  shapes.push_back(
      std::make_unique<Segment<2>>(Point<2>({0, 129}), Point<2>({129, 129})));
  shapes.push_back(
      std::make_unique<Segment<2>>(Point<2>({129, 129}), Point<2>({129, 0})));

  RigidBody<2> solid(Point<2>({0, 0}), std::move(shapes));

  draw(solid);
  return 0;
}

#define VIEWPORT_WIDTH 130
#define VIEWPORT_HEIGHT 130

template <unsigned int dim> void draw(RigidBody<dim> &solid) {
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
    std::cout.width(3);
    std::cout << y << "|";
    solid.draw(std::cout, y, VIEWPORT_WIDTH) << std::endl;
  }

  for (int i = 0; i < 3; i++) {
    std::cout << " ";
  }
  std::cout << "" << std::endl;
  std::cout.width(4);
  std::cout << "y" << std::endl;
};
