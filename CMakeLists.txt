cmake_minimum_required(VERSION 2.8)
project(test)
add_subdirectory(DebugPrintf)
add_subdirectory(libfdr)

set(CMAKE_BUILD_TYPE Debug)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libfdr)

if (EXISTS "${CMAKE_SOURCE_DIR}/binaries/libigraph.a")
  set(USE_IGRAPH ON)
endif ()

if (USE_IGRAPH)
  add_library(igraph STATIC IMPORTED)
  set_target_properties(igraph PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/binaries/libigraph.a)
  set(IGRAPH_LIBS igraph m)
endif (USE_IGRAPH)

add_executable(pr test.c)
target_link_libraries(pr ${IGRAPH_LIBS} fdr)
