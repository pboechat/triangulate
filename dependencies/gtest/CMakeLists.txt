cmake_minimum_required(VERSION 3.10)

project(gtest)

file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/gtest/*.h" "${PROJECT_SOURCE_DIR}/include/gtest/internal/*.h")
file(GLOB PRIVATE_HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cc")

source_group("include" FILES ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${PUBLIC_HEADERS} ${PRIVATE_HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
if(MSVC)
  target_compile_options(${PROJECT_NAME} PUBLIC /wd4996)
endif()
