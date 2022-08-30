include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

add_executable(ti_render.test ./main.cpp)

target_link_libraries(ti_render.test ti_render)
