cmake_minimum_required(VERSION 3.20)

project(convex_hull)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

source_group("includes" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} framework triangulate)
