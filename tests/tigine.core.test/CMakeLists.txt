include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

add_executable(tigine.core.test ./test.cpp)

target_link_libraries(tigine.core.test tigine.core)

add_custom_command(TARGET tigine.core.test POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/asset
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/asset ${CMAKE_CURRENT_BINARY_DIR}/asset
)