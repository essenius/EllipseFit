cmake_minimum_required(VERSION 3.14)

project(EllipseFit VERSION 0.0.1) #name of your project

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Main in EllipseFit: adding lib")

add_subdirectory(lib)

message(STATUS "Main in EllipseFit: matrixSourceDir=${matrixSourceDir}")

message(STATUS "Main in EllipseFit: adding src")

add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(STATUS "Main in EllipseFit: adding test")

  enable_testing()
  add_subdirectory(test)
endif()
