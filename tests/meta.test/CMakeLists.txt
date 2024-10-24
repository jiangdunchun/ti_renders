file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(meta.test ${SRC_FILES})
target_link_libraries(meta.test meta)


file(GLOB_RECURSE HEAD_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hxx")
set(GENERATED_HEAD_FILE ${CMAKE_CURRENT_SOURCE_DIR}/meta_generated/meta.generated.h)
set(GENERATED_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/meta_generated/meta.generated.cpp)
add_custom_target(meta_parser
    COMMAND ${META_PARSER} ${HEAD_FILES} ${GENERATED_HEAD_FILE} ${GENERATED_SOURCE_FILE} "$<JOIN:$<TARGET_PROPERTY:meta.test,INCLUDE_DIRECTORIES>, -I >")
add_dependencies(meta.test meta_parser)
