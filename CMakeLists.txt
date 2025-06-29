cmake_minimum_required(VERSION 3.15)
project(MyPlatformer)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(engine)
add_subdirectory(game)

set(CMAKE_BUILD_TYPE Debug)