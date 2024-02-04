cmake_minimum_required(VERSION 3.10)

project(freetype)

if (NOT WIN32)
	message(FATAL "platform not supported")
endif ()

file(GLOB PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/ft2build.h" "include/freetype/*.h")
file(GLOB PUBLIC_CONFIG_HEADERS "${PROJECT_SOURCE_DIR}/include/freetype/config/*.h")
file(GLOB PRIVATE_HEADERS "${PROJECT_SOURCE_DIR}/include/freetype/internal/*.h")

set(SOURCES
  "${PROJECT_SOURCE_DIR}/src/autofit/autofit.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftbase.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftbbox.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftbdf.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftbitmap.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftcid.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftfstype.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftgasp.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftglyph.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftgxval.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftinit.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftmm.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftotval.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftpatent.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftpfr.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftstroke.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftsynth.c"
  "${PROJECT_SOURCE_DIR}/src/base/fttype1.c"
  "${PROJECT_SOURCE_DIR}/src/base/ftwinfnt.c"
  "${PROJECT_SOURCE_DIR}/src/bdf/bdf.c"
  "${PROJECT_SOURCE_DIR}/src/bzip2/ftbzip2.c"
  "${PROJECT_SOURCE_DIR}/src/cache/ftcache.c"
  "${PROJECT_SOURCE_DIR}/src/cff/cff.c"
  "${PROJECT_SOURCE_DIR}/src/cid/type1cid.c"
  "${PROJECT_SOURCE_DIR}/src/gzip/ftgzip.c"
  "${PROJECT_SOURCE_DIR}/src/lzw/ftlzw.c"
  "${PROJECT_SOURCE_DIR}/src/pcf/pcf.c"
  "${PROJECT_SOURCE_DIR}/src/pfr/pfr.c"
  "${PROJECT_SOURCE_DIR}/src/psaux/psaux.c"
  "${PROJECT_SOURCE_DIR}/src/pshinter/pshinter.c"
  "${PROJECT_SOURCE_DIR}/src/psnames/psnames.c"
  "${PROJECT_SOURCE_DIR}/src/raster/raster.c"
  "${PROJECT_SOURCE_DIR}/src/sdf/sdf.c"
  "${PROJECT_SOURCE_DIR}/src/sfnt/sfnt.c"
  "${PROJECT_SOURCE_DIR}/src/smooth/smooth.c"
  "${PROJECT_SOURCE_DIR}/src/svg/svg.c"
  "${PROJECT_SOURCE_DIR}/src/truetype/truetype.c"
  "${PROJECT_SOURCE_DIR}/src/type1/type1.c"
  "${PROJECT_SOURCE_DIR}/src/type42/type42.c"
  "${PROJECT_SOURCE_DIR}/src/winfonts/winfnt.c"
  "${PROJECT_SOURCE_DIR}/src/windows/ftdebug.c"
  "${PROJECT_SOURCE_DIR}/src/windows/ftsystem.c"
)

source_group("include" FILES ${HEADERS})
source_group("src" FILES ${SOURCES})

add_library(${PROJECT_NAME}
  ${PUBLIC_HEADERS}
  ${PUBLIC_CONFIG_HEADERS}
  ${PRIVATE_HEADERS}
  ${SOURCES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES C_VISIBILITY_PRESET hidden)

target_compile_definitions(${PROJECT_NAME} PRIVATE FT2_BUILD_LIBRARY _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)

# Pick up ftconfig.h and ftoption.h generated above, first.
target_include_directories(
  ${PROJECT_NAME}
    PUBLIC
      $<INSTALL_INTERFACE:include/freetype2>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
      ${CMAKE_CURRENT_BINARY_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${CMAKE_CURRENT_BINARY_DIR}/include/freetype/config
)
target_link_libraries(${PROJECT_NAME} PRIVATE zlib)
