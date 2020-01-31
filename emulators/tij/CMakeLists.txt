##########################################
##	Macsa TIJ emulator
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME TIJEmulator)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

include(${PROJECT_SOURCE_DIR}/../extras/macsa.cmake)

if(UNIX)
	add_compile_options(-fPIC)
	set(EXTERNAL_LIBS	-lpthread)
endif()

if (NOT VIRTUAL_MOCK)
	add_definitions(-DVIRTUAL_MOCK=)
endif()


set(TIJ_EMULATOR_VERSION_MAJOR 1)
set(TIJ_EMULATOR_VERSION_MINOR 0)
set(TIJ_EMULATOR_VERSION_PATCH 0)
set(TIJ_EMULATOR_VERSION ${TIJ_EMULATOR_VERSION_MAJOR}.${TIJ_EMULATOR_VERSION_MINOR}.${TIJ_EMULATOR_VERSION_PATCH})


add_definitions(-DEMULATOR_VERSION_MAJOR=${TIJ_EMULATOR_VERSION_MAJOR})
add_definitions(-DEMULATOR_VERSION_MINOR=${TIJ_EMULATOR_VERSION_MINOR})
add_definitions(-DEMULATOR_VERSION_PATCH=${TIJ_EMULATOR_VERSION_PATCH})
add_definitions(-DEMULATOR_VERSION_STR="${TIJ_EMULATOR_VERSION}")


set(SOURCES)
set(HEADERS)
set(INCLUDES)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/../core ${CMAKE_BINARY_DIR}/mcomms)

SET (INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/../core/include
	${PROJECT_SOURCE_DIR}/../network/include
	${PROJECT_SOURCE_DIR}/../printers/include
	${LIB_PREFIX}/include
	${INCLUDES}
)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})

include_directories(${INCLUDES})

###########################
## Install targets
###########################

link_directories(
	${CMAKE_BINARY_DIR}/core
	${CMAKE_BINARY_DIR}/network
	${CMAKE_BINARY_DIR}/printers/tij
	)

add_executable( ${PROJECT_NAME} ${SOURCES} ${HEADERS})
# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${EXTERNAL_LIBS} MComms MNetwork TijLibrary)
