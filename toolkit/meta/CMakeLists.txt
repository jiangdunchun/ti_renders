file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_library(meta STATIC ${SRC_FILES})

target_include_directories(meta PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})




