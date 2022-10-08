cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(ti_renders)

add_subdirectory(./3rdparty)

add_subdirectory(./tigine.core)

add_subdirectory(tigine.graphic)

add_subdirectory(./ti_render)

add_subdirectory(./tests)


