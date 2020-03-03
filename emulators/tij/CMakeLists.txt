##########################################
##	Macsa TIJ emulator
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME TIJEmulator)
project(${PROJECT_NAME})

message("Parsing " ${TIJ_LIBRARY_NAME} " definitions")
message("PROJECT_NAME: " ${PROJECT_NAME})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

option(BUILD_EMULATOR_LIBS "Add MComms cmake projects" OFF)

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

include(${PROJECT_SOURCE_DIR}/../toolchain/cmake/macsa.cmake)
set(UTILS_DIR ${PROJECT_SOURCE_DIR}/../utils)

if(UNIX)
	add_compile_options(-fPIC)
	set(EXTERNAL_LIBS	-lpthread)
endif()

set(TIJ_EMULATOR_VERSION_MAJOR 1)
set(TIJ_EMULATOR_VERSION_MINOR 0)
set(TIJ_EMULATOR_VERSION_PATCH 0)
set(TIJ_EMULATOR_VERSION ${TIJ_EMULATOR_VERSION_MAJOR}.${TIJ_EMULATOR_VERSION_MINOR}.${TIJ_EMULATOR_VERSION_PATCH})


add_definitions(-DEMULATOR_VERSION_MAJOR=${TIJ_EMULATOR_VERSION_MAJOR})
add_definitions(-DEMULATOR_VERSION_MINOR=${TIJ_EMULATOR_VERSION_MINOR})
add_definitions(-DEMULATOR_VERSION_PATCH=${TIJ_EMULATOR_VERSION_PATCH})
add_definitions(-DEMULATOR_VERSION_STR="${TIJ_EMULATOR_VERSION}")

###########################

set(SOURCES)
set(HEADERS)
set(INCLUDES)
set(UIS)
set(RESOURCES)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src		${PROJECT_BINARY_DIR}/tij/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include	${PROJECT_BINARY_DIR}/tij/include)
if (BUILD_EMULATOR_LIBS)
	add_subdirectory(${PROJECT_SOURCE_DIR}/../core		${PROJECT_BINARY_DIR}/core)
endif()

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})
set(INCLUDES ${INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../core/include
    ${PROJECT_SOURCE_DIR}/../network/include
    ${PROJECT_SOURCE_DIR}/../printers/include
    ${PROJECT_SOURCE_DIR}/../printers/tij/include
    ${LIB_PREFIX}/include
	${UTILS_DIR}/include
)

include_directories(${INCLUDES})

# Next lines needed for building all Qt projects
find_package( Qt4 REQUIRED )
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${PROJECT_BINARY_DIR})

# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HEADERS} )

###########################
## Install targets
###########################

link_directories(
	${PROJECT_BINARY_DIR}/core
	${PROJECT_BINARY_DIR}/core/network
	${PROJECT_BINARY_DIR}/core/printers/tij
    )

# compile
if (WIN32)
    add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
elseif(UNIX)
    add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
endif()
# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} MComms MNetwork TijLibrary)

