set(GRAPHIC_API "vulkan" CACHE STRING "gl430 || vulkan" FORCE)
#set(GRAPHIC_API "gl430" CACHE STRING "gl430 || vulkan" FORCE)

if(${GRAPHIC_API} STREQUAL "vulkan")
	message(STATUS "--->Using vulkan as graphic api")
	add_definitions(-DUSING_VULKAN)
	file(GLOB_RECURSE SRC_FILES ./vulkan/*.cpp)
else()
	message(STATUS "--->Using gl430 as graphic api")
	add_definitions(-DUSING_GL430)
	file(GLOB_RECURSE SRC_FILES ./gl430/*.cpp)
endif()

include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

find_package(Vulkan REQUIRED FATAL_ERROR)
include_directories(${Vulkan_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

#file(GLOB_RECURSE SRC_FILES ./*.cpp)
add_executable(tigine.graphic ${SRC_FILES} main.cpp)

target_link_libraries(tigine.graphic glad glfw ${Vulkan_LIBRARY})




