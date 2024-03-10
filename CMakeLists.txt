cmake_minimum_required(VERSION 3.14)

set(fitName EllipseFit)
set(testFitName ${fitName}Test)
set(matrixName matrix) # lower case is important for fetching the library
set(matrixLibName Matrix) # the name of the library as defined in the CMakeLists.txt of the library

project(${fitName} VERSION 0.2.2 LANGUAGES CXX)

if ((CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(TOP_LEVEL ON)
else()
  set(TOP_LEVEL OFF)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/lib;${PROJECT_BINARY_DIR}/lib/cmake")

add_subdirectory(lib)

if (TOP_LEVEL) 
  message(STATUS "Top level project - enabling code coverage")
  set(CODE_COVERAGE ON)
  include(code-coverage)
  add_code_coverage()
endif()

add_subdirectory(src)

if(TOP_LEVEL)
  message(STATUS "Top level project - enabling tests")
  enable_testing()
  add_subdirectory(test)
  target_code_coverage(${testFitName} EXCLUDE build/_deps/googletest-src/* test/*) 
endif()

#install(TARGETS ${fitName} LIBRARY DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# to generate coverage report run 'make ccov-EllipseFitTest' and view build/ccov/EllipseFitTest/index.html