include(tools)

include(FindGit)
find_package(Git)

assertVariableSet(testLibName matrixLibName Git_FOUND)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG release-1.12.1
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable_With_Check(googletest)

add_executable(${testLibName} "")

# not using file(GLOB_RECURSE myHeaders LIST_DIRECTORIES true *.h) as explit listing is less error prone
target_sources (${testLibName} 
    PUBLIC TestHelper.h EllipseFitTest.h
    PRIVATE AngleTest.cpp CartesianEllipseTest.cpp CoordinateTest.cpp EllipseFitTest.cpp MathUtilsTest.cpp QuadraticEllipseTest.cpp TestHelper.cpp 
)

FetchContent_MakeAvailable_With_Check(${matrixName})

target_link_libraries(${testLibName} ${libName} gtest_main ${matrixLibName})

add_test(NAME ${testLibName} COMMAND ${testLibName})
