cmake_minimum_required(VERSION 3.14)

project(EllipseFit VERSION 0.0.1) #name of your project

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include(FindGit)
#find_package(Git)

# if (NOT Git_FOUND)
# 	message(FATAL_ERROR "Git not found!")
# endif ()

# include (FetchContent)

# FetchContent_Declare(
#     matrixlib
#     GIT_REPOSITORY https://github.com/essenius/matrix
#     GIT_TAG main    
#     SOURCE_SUBDIR src
#     SOURCE_DIR matrixlib
# )

# FetchContent_MakeAvailable(matrixlib)

# FetchContent_GetProperties(matrixlib SOURCE_DIR matrixSourceDir BINARY_DIR matrixBinaryDir)

# message(matrixSourceDir="${matrixSourceDir}")
# message(matrixBinaryDir="${matrixBinaryDir}")

# include(ExternalProject)
# ExternalProject_Add(
#     gtest
#     GIT_REPOSITORY https://github.com/google/googletest
#     GIT_TAG release-1.12.1
#     PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
#     INSTALL_COMMAND ""
# )
# ExternalProject_Get_Property(gtest source_dir binary_dir)

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
# add_executable(runUnitTests test/EllipseFitTest.cpp test/TestHelper.cpp src/EllipseFit.cpp src/Angle.cpp src/CartesianEllipse.cpp src/QuadraticEllipse.cpp src/Coordinate.cpp src/MathUtils.cpp)
# add_library(EllipseFit src/EllipseFit.cpp src/CartesianEllipse.cpp src/QuadraticEllipse.cpp src/Coordinate.cpp src/Angle.cpp src/MathUtils.cpp)
# add_dependencies(runUnitTests gtest)
# message(source_dir="${source_dir}")
# include_directories(${source_dir}/googletest/include)
# message(binary_dir="${binary_dir}")
# target_link_libraries(runUnitTests ${binary_dir}/lib/libgtest.a)
# target_link_libraries(runUnitTests ${binary_dir}/lib/libgtest_main.a)

#add_test(NAME runUnitTests COMMAND runUnitTests)
