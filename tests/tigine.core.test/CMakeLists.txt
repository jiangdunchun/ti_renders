include_directories(${HEADERONLY_3RDPARTY_INCLUDE_DIR})

add_executable(tigine.core.test ./test.cpp)

target_link_libraries(tigine.core.test tigine.core)

set(TEST_ASSET_DIR ./asset)

add_definitions(-DTEST_ASSET_DIR="${TEST_ASSET_DIR}/")

add_custom_command(TARGET tigine.core.test POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${TEST_ASSET_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_ASSET_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${TEST_ASSET_DIR}
)
