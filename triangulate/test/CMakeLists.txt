cmake_minimum_required(VERSION 3.20)

project(triangulate_tests)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

source_group("src" FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest triangulate)