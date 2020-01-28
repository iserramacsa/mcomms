##########################################
##	Project definition script
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME MConsole)

project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

## Include macsa common code
include($ENV{HOME}/workspace/tools/cmake/macsa.cmake)

if(UNIX)
	add_compile_options(-fPIC)
	set(EXTERNAL_LIBS	-lpthread)
endif()

if (NOT VIRTUAL_MOCK)
	add_definitions(-DVIRTUAL_MOCK=)
endif()

##Adding sources
set(SOURCES)
set(HEADERS)
set(INCLUDES)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/console/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/console/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/../core ${CMAKE_BINARY_DIR}/core)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})
set(INCLUDES 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/../core/include
	${PROJECT_SOURCE_DIR}/../network/include
	${PROJECT_SOURCE_DIR}/../printers/include
	${PROJECT_SOURCE_DIR}/../printers/tij/include
	${LIB_PREFIX}/include
	${INCLUDES}
)

include_directories(${INCLUDES})


###########################
## Install targets
###########################
#Building project
# Add all the source files needed to build the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${INCLUDES})

# Include the directory where MyLibrary project is. Otherwise, we can't use the
# library
#add_subdirectory(libraries/MyLibrary)

link_directories(
	${CMAKE_BINARY_DIR}/core
	${CMAKE_BINARY_DIR}/network
	${CMAKE_BINARY_DIR}/printers/tij
)
# Link the executable and the library together
target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS} MComms MNetwork TijLibrary)

