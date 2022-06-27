include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

add_executable(fft_water_simulation ./main.cpp)

target_link_libraries(fft_water_simulation glad glfw)

