
include(FindGit)
find_package(Git)

if (NOT Git_FOUND)
	message(FATAL_ERROR "Git not found!")
endif ()

include (FetchContent)

set (libName matrixlib)

FetchContent_Declare(
    ${libName}
    GIT_REPOSITORY https://github.com/essenius/matrix
    GIT_TAG main    
    SOURCE_SUBDIR src
    SOURCE_DIR ${libName}
)

FetchContent_MakeAvailable(${libName})

FetchContent_GetProperties(${libName} SOURCE_DIR matrixSourceDir BINARY_DIR matrixBinaryDir)

message(STATUS "${libName} matrixSourceDir = ${matrixSourceDir}")
message(STATUS "${libName} matrixBinaryDir = ${matrixBinaryDir}")
message(STATUS "${libName} cmake binary dir = ${CMAKE_BINARY_DIR}")
message(STATUS "${libName} includes = ${INCLUDE_DIRECTORIES}")
