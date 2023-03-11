add_executable(tigine.rhi.tests.rotate_texture ./main.cpp)

target_link_libraries(tigine.rhi.tests.rotate_texture tigine.rhi)


include(${PROJECT_SOURCE_DIR}/cmake/ShaderCompiler.cmake)
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.vert"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.frag"
                                            "${CMAKE_CURRENT_SOURCE_DIR}/shader/*.comp")
compile_shader("${SHADER_FILES}" ${CMAKE_CURRENT_SOURCE_DIR}/shader)




