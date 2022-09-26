include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_library(ti_render STATIC ${SRC_FILES})

target_include_directories(ti_render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(ti_render md5 glad glfw json11 assimp)




