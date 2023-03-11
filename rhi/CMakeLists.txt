set(GRAPHIC_API "vulkan" CACHE STRING "gl430 || vulkan" FORCE)
#set(GRAPHIC_API "gl430" CACHE STRING "gl430 || vulkan" FORCE)

if(${GRAPHIC_API} STREQUAL "vulkan")
	add_definitions(-DUSING_VULKAN)

	file(GLOB_RECURSE GRAPHIC_SRC_FILES ./vulkan/*.cpp)

	find_package(Vulkan REQUIRED FATAL_ERROR)
	
	set(GRAPHIC_INCLUDE_DIRS ${Vulkan_INCLUDE_DIR})

	set(GRAPHIC_LINKED_LIBS glfw ${Vulkan_LIBRARY})
	
else()
	add_definitions(-DUSING_GL430)

	file(GLOB_RECURSE GRAPHIC_SRC_FILES ./gl430/*.cpp)

	set(GRAPHIC_INCLUDE_DIRS)

	set(GRAPHIC_LINKED_LIBS glad glfw)
endif()

message(STATUS "*****tigine.rhi*****")
message(STATUS "Using ${GRAPHIC_API} as graphic api:")
message(STATUS "GRAPHIC_SRC_FILES: ${GRAPHIC_SRC_FILES}")
message(STATUS "GRAPHIC_INCLUDE_DIRS: ${GRAPHIC_INCLUDE_DIRS}")
message(STATUS "GRAPHIC_LINKED_LIBS: ${GRAPHIC_LINKED_LIBS}")
message(STATUS "********************")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
include_directories(${GRAPHIC_INCLUDE_DIRS})

add_library(tigine.rhi STATIC ${GRAPHIC_SRC_FILES} "rhi.cpp")

target_link_libraries(tigine.rhi ${GRAPHIC_LINKED_LIBS})

target_include_directories(tigine.rhi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


