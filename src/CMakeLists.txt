include(tools)

include(FindGit)
find_package(Git)

assertVariableSet(fitName matrixName Git_FOUND)

# we need the source and binaries locations of the Matrix library that was already built in lib
FetchContent_MakeAvailable_With_Check(${matrixName})

add_library(${fitName} "")

#file(GLOB_RECURSE myHeaders LIST_DIRECTORIES true *.h)
#file(GLOB_RECURSE mySources LIST_DIRECTORIES true *.cpp)

set(myHeaders Angle.h CartesianEllipse.h Coordinate.h EllipseFit.h MathUtils.h QuadraticEllipse.h)
set(mySources Angle.cpp CartesianEllipse.cpp Coordinate.cpp EllipseFit.cpp MathUtils.cpp QuadraticEllipse.cpp) 
target_sources (${fitName} PUBLIC ${myHeaders} PRIVATE ${mySources})
target_link_libraries(${fitName} PUBLIC Matrix)
target_include_directories(${fitName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${${matrixName}_SOURCE_DIR}/src)

# show all variables. 
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()