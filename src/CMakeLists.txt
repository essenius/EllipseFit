include(tools)

assertVariableSet(fitName matrixName)

message(STATUS "In EllipseFit ${fitName} src: CMAKE_PROJECT_NAME=${CMAKE_PROJECT_NAME}")

message(STATUS "CMAKE_CURRENT_SOURCE_DIR= ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR= ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "PROJECT_BINARY_DIR=       ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR=         ${CMAKE_BINARY_DIR}")

message(STATUS "matrixName=${matrixName}")
message(STATUS "${fitName}_SOURCE_DIR=   ${${fitName}_SOURCE_DIR}")
message(STATUS "${fitName}_BINARY_DIR=   ${${fitName}_BINARY_DIR}")
# we need the source and binaries locations of the Matrix library that was already built in lib

FetchContent_MakeAvailable_With_Check(${matrixName})

message(STATUS "${matrixName}_SOURCE_DIR= ${${matrixName}_SOURCE_DIR}")
message(STATUS "${matrixName}_BINARY_DIR= ${${matrixName}_BINARY_DIR}")

add_library(${fitName} "")

# show all variables. 
file(APPEND ${PROJECT_BINARY_DIR}/output.txt , "Variables for EllipseFit:")
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${_variableName}=${${_variableName}}\n")
endforeach()

set(myHeaders Angle.h CartesianEllipse.h Coordinate.h EllipseFit.h MathUtils.h QuadraticEllipse.h)
set(mySources Angle.cpp CartesianEllipse.cpp Coordinate.cpp EllipseFit.cpp MathUtils.cpp QuadraticEllipse.cpp) 
target_sources (${fitName} PUBLIC ${myHeaders} PRIVATE ${mySources})
target_link_libraries(${fitName} PUBLIC Matrix)
target_include_directories(${fitName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${${matrixName}_SOURCE_DIR}/src)



install(TARGETS ${fitName} DESTINATION lib) # ${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${myHeaders} DESTINATION include) 