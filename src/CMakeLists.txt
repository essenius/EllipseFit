include(tools)

include(FindGit)
find_package(Git)

assertVariableSet(libName matrixLibName Git_FOUND)

# we need the source and binaries locations of the Matrix library that was already built in lib
FetchContent_MakeAvailable_With_Check(${matrixLibName})

add_library(${libName} "")

file(GLOB_RECURSE myHeaders LIST_DIRECTORIES true *.h)
file(GLOB_RECURSE mySources LIST_DIRECTORIES true *.cpp)
target_sources (${libName} PUBLIC ${myHeaders} PRIVATE ${mySources})
target_link_libraries(${libName} PRIVATE ${${matrixLibName}_BINARY_DIR}/libMatrix.a)
target_include_directories(${libName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${${matrixLibName}_SOURCE_DIR}/src)

# show all variables. 
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()