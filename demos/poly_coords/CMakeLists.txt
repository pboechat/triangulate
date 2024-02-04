cmake_minimum_required(VERSION 3.20)

project(poly_coords)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

source_group("src" FILES ${SOURCES})

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
target_link_libraries(${PROJECT_NAME} framework triangulate)
