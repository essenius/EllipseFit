cmake_minimum_required(VERSION 3.14)

set(libName EllipseFit)
set(testLibName ${libName}Test)
set(matrixName matrix) # lower case is important for fetching the library
set(matrixLibName Matrix) # the name of the library as defined in the CMakeLists.txt of the library

project(${libName} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CODE_COVERAGE ON)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${PROJECT_SOURCE_DIR}/lib;${PROJECT_BINARY_DIR}/lib/cmake")

add_subdirectory(lib)

include(code-coverage)
add_code_coverage()

add_subdirectory(src)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  enable_testing()
  add_subdirectory(test)
  target_code_coverage(${testLibName} EXCLUDE build/_deps/googletest-src/* test/*) 
endif()

# to generate coverage report run 'make ccov-EllipseFitTest' and view build/ccov/EllopseFitTest/index.html