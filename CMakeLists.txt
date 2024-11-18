cmake_minimum_required(VERSION 3.14)

set(fitName EllipseFit)
set(testFitName ${fitName}Test)
set(matrixName matrix) # lower case is important for fetching the library
set(matrixLibName Matrix) # the name of the library as defined in the CMakeLists.txt of the library

# if CMAKE_INSTALL_PREFIX is set to its default value, use the dist folder in the project source directory instead
if (NOT DEFINED CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX STREQUAL "/usr/local" OR CMAKE_INSTALL_PREFIX STREQUAL "C:/Program Files")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "Installation Directory" FORCE)
  set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/dist" CACHE PATH "Prefix Path for Dependencies" FORCE)
  set(CUSTOM_INSTALL_PREFIX_INITIALIZED 1)
else()
  set(CUSTOM_INSTALL_PREFIX_INITIALIZED 0)
endif()

project(${fitName} VERSION 0.2.6 LANGUAGES CXX)

message(STATUS "after project: CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} and CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")

# We don't want to run tests for the library when it is included as a subdirectory or when we run it from vcpkg
if ((CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR) AND NOT DEFINED VCPKG_TARGET_TRIPLET)
  set(TOP_LEVEL ON)
  if(WIN32)
    set(CMAKE_GENERATOR "MinGW Makefiles")
  endif()
else()
  set(TOP_LEVEL OFF)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/lib;${PROJECT_BINARY_DIR}/lib/cmake")

add_subdirectory(lib)

# Only enable code coverage if we test. Disabling code coverage for Windows as we still need to get that working.
if (TOP_LEVEL AND NOT DEFINED WIN32) 
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
  if (CODE_COVERAGE)
    target_code_coverage(${testFitName} EXCLUDE build/_deps/googletest-src/* test/*) 
  endif()
endif()

# to generate coverage report run 'make ccov-EllipseFitTest' and view build/ccov/EllipseFitTest/index.html