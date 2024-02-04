cmake_minimum_required(VERSION 3.20)

project(triangulate)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/triangulate/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(test)

