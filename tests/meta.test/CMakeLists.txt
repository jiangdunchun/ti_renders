file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(meta.test ${SRC_FILES})
target_link_libraries(meta.test meta)


file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx")
include(${META_PARSER_CMAKE})
meta_pre_compile(${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/meta_generated/meta.generated.h ${CMAKE_CURRENT_SOURCE_DIR}/meta_generated/meta.generated.cpp)
