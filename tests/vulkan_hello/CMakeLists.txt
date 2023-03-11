include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

find_package(Vulkan REQUIRED FATAL_ERROR)
include_directories(${Vulkan_INCLUDE_DIR})

add_executable(vulkan_hello test.cpp)


include(../../cmake/ShaderCompiler.cmake)

file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.vert"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.frag"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.comp")

compile_shader(
  "${SHADER_FILES}"
  ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(vulkan_hello glfw ${Vulkan_LIBRARY})