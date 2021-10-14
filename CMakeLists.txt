cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(ASSERT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assert)

add_subdirectory(./third_party)
add_subdirectory(./ti_render)
add_subdirectory(./ti_render.test)


