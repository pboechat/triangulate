cmake_minimum_required(VERSION 3.10)

project(zlib)

list(APPEND HEADERS "${PROJECT_SOURCE_DIR}/include/zstd.h")
list(APPEND SOURCES "${PROJECT_SOURCE_DIR}/src/zstd.c")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
if(UNIX)
	target_link_libraries(${PROJECT_NAME} pthread)
endif()
