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
add_executable(tigine.graphic ${SRC_FILES})

target_link_libraries(tigine.graphic glad glfw)




