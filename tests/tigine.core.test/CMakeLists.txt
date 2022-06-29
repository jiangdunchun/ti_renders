include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

add_executable(tigine.core.test ./test.cpp)

target_link_libraries(tigine.core.test tigine.core)