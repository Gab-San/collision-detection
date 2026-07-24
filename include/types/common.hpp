#ifndef __TYPES_COMMON_HPP
#define __TYPES_COMMON_HPP

#include "lbm-sim/collision-detection/core/point.hpp"
#include "lbm-sim/collision-detection/core/vector.hpp"

#include <cstddef>

namespace CollisionDetection {
namespace types {
template <int dim> using ValuePoint = utils::Point<double, dim>;

template <int dim> using IndexPoint = utils::Point<unsigned int, dim>;

template <int dim> using DimPoint = utils::Point<std::size_t, dim>;

template <int dim> using Coordinate = utils::Point<int, dim>;

} // namespace types
} // namespace CollisionDetection

#endif // __TYPES_COMMON_HPP
