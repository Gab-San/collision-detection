cmake_minimum_required(VERSION 4.3)

project(lbm-collision-detection)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

file(
  GLOB_RECURSE
  COLLISION_DETECTION_CORE_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

add_library(${PROJECT_NAME} INTERFACE ${COLLISION_DETECTION_CORE_HEADERS})
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_subdirectory(test)

