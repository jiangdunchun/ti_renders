set(GRAPHIC_API "gl430plus" CACHE STRING "gl430plus || vulkan" FORCE)

if(${GRAPHIC_API} STREQUAL "vulkan")
	message(STATUS "using vulkan as graphic api")
	add_definitions(-DUSING_VULKAN_AS_GRAPHIC_API)
else()
	message(STATUS "using gl430plus as graphic api")
	add_definitions(-DUSING_GL430PLUS_AS_GRAPHIC_API)
endif()

include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_library(tigine.graphic STATIC ${SRC_FILES})

target_include_directories(tigine.graphic  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_link_libraries(tigine.graphic  glad glfw)




