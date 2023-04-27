
include(tools)
include(FindGit)
find_package(Git)

assertVariableSet(matrixLibName Git_FOUND)

include (FetchContent)

FetchContent_Declare(
    ${matrixLibName}
    GIT_REPOSITORY https://github.com/essenius/matrix
    GIT_TAG main    
    SOURCE_SUBDIR src
    SOURCE_DIR ${matrixLibName}
)

FetchContent_Declare(
    code-coverage
    URL https://raw.githubusercontent.com/StableCoder/cmake-scripts/23.04/code-coverage.cmake
    SOURCE_DIR cmake
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_MakeAvailable_With_Check(${matrixLibName})

FetchContent_MakeAvailable_With_Check(code-coverage)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()