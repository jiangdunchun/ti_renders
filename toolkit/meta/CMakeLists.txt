file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_library(meta STATIC ${SRC_FILES})

target_include_directories(meta PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(META_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "meta include directory")
set(META_PARSER_DIR ${META_INCLUDE_DIR}/parser CACHE INTERNAL "meta parser directory")
set(META_PARSER_CMAKE ${META_PARSER_DIR}/meta_parser.cmake CACHE INTERNAL "meta parser cmake file path")



