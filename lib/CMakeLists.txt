
include(tools)
include(FindGit)
find_package(Git)


assertVariableSet(matrixName GIT_FOUND)

include (FetchContent)

FetchContent_Declare(
    ${matrixName}
    GIT_REPOSITORY https://github.com/essenius/matrix
    GIT_TAG main    
    # SOURCE_DIR ${matrixName}
)

FetchContent_MakeAvailable_With_Check(${matrixName})

# show all variables. 
file(APPEND ${PROJECT_BINARY_DIR}/output.txt , "----- in lib\n")
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
   file(APPEND ${PROJECT_BINARY_DIR}/output.txt , "${_variableName}=${${_variableName}}\n")
endforeach()
file(APPEND ${PROJECT_BINARY_DIR}/output.txt , "----- end lib\n")


if (TOP_LEVEL)
    FetchContent_Declare(
        code-coverage
        URL https://raw.githubusercontent.com/StableCoder/cmake-scripts/23.04/code-coverage.cmake
        SOURCE_DIR cmake
        DOWNLOAD_NO_EXTRACT TRUE
    )
    FetchContent_MakeAvailable_With_Check(code-coverage)
endif()


