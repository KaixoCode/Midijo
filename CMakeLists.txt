cmake_minimum_required (VERSION 3.0)
set(PRJ_NAME "Midijo")
set(CMAKE_CXX_STANDARD 20)
set(MIDIJO_SRC "${${PRJ_NAME}_SOURCE_DIR}/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${MIDIJO_SRC}/cmake/")

# Main library linking and including
project (${PRJ_NAME})

file(GLOB_RECURSE MIDIJO_SOURCE
  "${MIDIJO_SRC}source/*.cpp"
  "${MIDIJO_SRC}include/*.hpp"
)

set(MIDIJO_INCLUDE_DIRS
  ${MIDIJO_SRC}include/
)

option(MIDIJO_BUILD_DOCS "Build Docs" OFF)
option(MIDIJO_BUILD_EXAMPLE "Build Example" ON)

# Add the library
add_library(${PRJ_NAME} STATIC ${MIDIJO_SOURCE})

target_include_directories(${PRJ_NAME} PUBLIC
  ${MIDIJO_INCLUDE_DIRS}
)

target_link_libraries(${PRJ_NAME}
  winmm
)

# Group source according to folder layout
source_group(TREE ${MIDIJO_SRC} FILES ${MIDIJO_SOURCE})

# PCH
target_precompile_headers(${PRJ_NAME} PUBLIC "${MIDIJO_SRC}include/Midijo/pch.hpp")

# Example project
if(MIDIJO_BUILD_EXAMPLE)
set(EXM_NAME "MidijoExample")
project (${EXM_NAME})
set(EXM_SRC "${${EXM_NAME}_SOURCE_DIR}/")
file(GLOB_RECURSE EXAMPLE_SOURCE "${EXM_SRC}example/*.cpp")
add_executable(${EXM_NAME} ${EXAMPLE_SOURCE})
target_include_directories(${EXM_NAME} PUBLIC "${MIDIJO_SRC}include/")
target_link_libraries(${EXM_NAME} ${PRJ_NAME})
source_group(TREE ${EXM_SRC} FILES ${EXAMPLE_SOURCE})
endif()

if(MIDIJO_BUILD_DOCS)
add_subdirectory("docs")
endif()