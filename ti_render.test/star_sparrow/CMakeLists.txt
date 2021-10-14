project(star_sparrow)

file(COPY ${ASSERT_DIR}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${STB_INCLUDE_DIR})
include_directories(${RAPIDJSON_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${MD5_INCLUDE_DIR})
include_directories(${GLAD_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${TI_RENDER_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ./main.cpp)

target_link_libraries(${PROJECT_NAME} ti_render glad glfw md5)



