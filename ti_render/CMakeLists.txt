set(TI_RENDER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ PARENT_SCOPE)

include_directories(${STB_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${MD5_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

file(GLOB_RECURSE CPP_SRC_LIST ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_library(ti_render ${CPP_SRC_LIST})