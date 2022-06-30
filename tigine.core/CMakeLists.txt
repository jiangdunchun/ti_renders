include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_library(tigine.core ${SRC_FILES})

target_include_directories(tigine.core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(tigine.core json11)



