include(FindGit)
find_package(Git)

if (NOT Git_FOUND)
	message(FATAL_ERROR "Git not found!")
endif ()

FetchContent_GetProperties(matrixlib SOURCE_DIR matrixSourceDir BINARY_DIR matrixBinaryDir)

set (libName ${PROJECT_NAME})

message(STATUS ellipseFit src: CMAKE_PROJECT_NAME="${CMAKE_PROJECT_NAME}")
add_library(${libName} "")
message(STATUS "${libName} src: CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message(STATUS "${libName} src: PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "${libName} src: CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "${libName} src: CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "${libName} src: CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "${libName} src: CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "${libName} src: CMAKE_INSTALL_PREFIX")
message(STATUS "matrixSourceDir=${matrixSourceDir}")
message(STATUS "matrixBinaryDir=${matrixBinaryDir}")

file(GLOB_RECURSE myHeaders LIST_DIRECTORIES true *.h)
file(GLOB_RECURSE mySources LIST_DIRECTORIES true *.cpp)
target_sources (${CMAKE_PROJECT_NAME} PUBLIC ${myHeaders} PRIVATE ${mySources})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${matrixBinaryDir}/libMatrix.a)
target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${matrixSourceDir}/src)
