add_executable(meta.test ./main.cpp ./meta.generated.cpp)

target_link_libraries(meta.test meta)


file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/*.hxx")
include(${META_PARSER_CMAKE})
meta_pre_compile(${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/meta.generated.cpp)
