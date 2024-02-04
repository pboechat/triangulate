cmake_minimum_required(VERSION 3.20)

project(framework)

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/include/framework/*.h")
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} SDL_draw SDL_ttf SDL triangulate)
add_dependencies(${PROJECT_NAME} assets)
