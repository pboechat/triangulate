cmake_minimum_required(VERSION 3.10)

project(SDL_draw)

set(HEADERS "${PROJECT_SOURCE_DIR}/include/SDL_draw.h")
set(SOURCES "${PROJECT_SOURCE_DIR}/src/SDL_draw.c")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} SDL)
