set(CMAKE_BUILD_TYPE Debug)

add_executable(CollisionArea "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
target_link_libraries(CollisionArea PRIVATE lbm-collision-detection)
