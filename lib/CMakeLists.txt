include(tools)
include(FindGit)
find_package(Git)

assertVariableSet(matrixName GIT_FOUND TOP_LEVEL)

include (FetchContent)

FetchContent_Declare(
    ${matrixName}
    GIT_REPOSITORY https://github.com/essenius/matrix
    GIT_TAG main    
)

Message(STATUS "executing FetchContent_MakeAvailable for ${matrixName}")

FetchContent_MakeAvailable_With_Check(${matrixName})

Message(STATUS "completed FetchContent_MakeAvailable for ${matrixName}")

if (TOP_LEVEL)
    FetchContent_Declare(
        code-coverage
        URL https://raw.githubusercontent.com/StableCoder/cmake-scripts/23.04/code-coverage.cmake
        SOURCE_DIR cmake
        DOWNLOAD_NO_EXTRACT TRUE
        URL_HASH SHA256=E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855
    )
    FetchContent_MakeAvailable_With_Check(code-coverage)
endif()
