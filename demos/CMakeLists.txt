cmake_minimum_required(VERSION 3.10)

set(BIN_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_custom_target(assets ALL)

add_custom_command(
	TARGET assets
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/assets ${BIN_DIRECTORY}/assets
	COMMENT "Copying assets to target directory."
)

foreach(CMAKE_CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CMAKE_CONFIGURATION_TYPE} CMAKE_CONFIGURATION_TYPE)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE} ${BIN_DIRECTORY})
endforeach(CMAKE_CONFIGURATION_TYPE)
set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY ${BIN_DIRECTORY})
set(CMAKE_DEBUG_POSTFIX d)

add_subdirectory(convex_hull)
add_subdirectory(ear_clipping)
add_subdirectory(framework)
add_subdirectory(poly_coords)