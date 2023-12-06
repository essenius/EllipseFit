include(tools)

assertVariableSet(fitName matrixName)

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "In EllipseFit ${fitName} src: CMAKE_PROJECT_NAME=${CMAKE_PROJECT_NAME}\n")

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "CMAKE_CURRENT_SOURCE_DIR= ${CMAKE_CURRENT_SOURCE_DIR}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "CMAKE_CURRENT_BINARY_DIR= ${CMAKE_CURRENT_BINARY_DIR}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "PROJECT_BINARY_DIR=       ${PROJECT_BINARY_DIR}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "CMAKE_BINARY_DIR=         ${CMAKE_BINARY_DIR}\n")

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "matrixName=${matrixName}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${fitName}_SOURCE_DIR=   ${${fitName}_SOURCE_DIR}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${fitName}_BINARY_DIR=   ${${fitName}_BINARY_DIR}\n")
# we need the source and binaries locations of the Matrix library that was already built in lib

FetchContent_MakeAvailable_With_Check(${matrixName})

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${matrixName}_SOURCE_DIR= ${${matrixName}_SOURCE_DIR}\n")
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${matrixName}_BINARY_DIR= ${${matrixName}_BINARY_DIR}\n")

add_library(${fitName} "")

# show all variables. 
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "Variables for EllipseFit:\n")
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    file(APPEND ${PROJECT_BINARY_DIR}/output.txt "${_variableName}=${${_variableName}}\n")
endforeach()

set(myHeaders Angle.h CartesianEllipse.h Coordinate.h EllipseFit.h MathUtils.h QuadraticEllipse.h)
set(mySources Angle.cpp CartesianEllipse.cpp Coordinate.cpp EllipseFit.cpp MathUtils.cpp QuadraticEllipse.cpp) 

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "executing target_sources\n")
target_sources (${fitName} PUBLIC ${myHeaders} PRIVATE ${mySources})

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "executing target_link_libraries\n")
target_link_libraries(${fitName} PUBLIC Matrix)
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "executing target_include_libraries\n")
target_include_directories(${fitName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} C:/Users/Rik.Essenius/source/repos/essenius/temp/vcpkg_installed/x64-windows/include)

file(APPEND ${PROJECT_BINARY_DIR}/output.txt "executing install TARGETS\n")
install(TARGETS ${fitName} DESTINATION lib) # ${CMAKE_CURRENT_BINARY_DIR})
file(APPEND ${PROJECT_BINARY_DIR}/output.txt "executing install FILES\n")
install(FILES ${myHeaders} DESTINATION include) 