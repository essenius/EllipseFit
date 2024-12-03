set(myHeaders Angle.h CartesianEllipse.h Coordinate.h EllipseFit.h MathUtils.h QuadraticEllipse.h)
set(mySources Angle.cpp CartesianEllipse.cpp Coordinate.cpp EllipseFit.cpp MathUtils.cpp QuadraticEllipse.cpp) 

if (ESP_PLATFORM AND DEFINED ENV{IDF_PATH})
    idf_component_register(SRCS ${mySources}
                    INCLUDE_DIRS "."
                    REQUIRES matrix)
else()
    include(tools)
    
    assertVariableSet(fitName matrixName)
    
    # we need the source and binaries locations of the Matrix library that was already built in lib
    
    message(STATUS "Adding library ${fitName}. CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} and CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
    
    add_library(${fitName} "")
    
    foreach (entry ${CMAKE_PREFIX_PATH})
        list(APPEND includeFolders ${entry}/include)
    endforeach() 
    
    message(STATUS "includeFolders=${includeFolders}")
    
    target_sources (${fitName} PUBLIC ${myHeaders} PRIVATE ${mySources})
    target_link_libraries(${fitName} PUBLIC Matrix)
    target_include_directories(${fitName} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${includeFolders})
    
    install(TARGETS ${fitName} DESTINATION lib) 
    install(FILES ${myHeaders} DESTINATION include) 
endif()
