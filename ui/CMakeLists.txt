##########################################
##	Macsa Communications library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME MCommsUI)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")


if (WIN32)
	message("Windows version")
	set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
elseif(UNIX)
	add_compile_options(-fPIC)
	if (CMAKE_CXX_COMPILER MATCHES "gnueabihf")
		message("Linux arm-gnueabihf")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-linux-gnueabihf)
	elseif(CMAKE_CXX_COMPILER MATCHES "gnueabi")
		message("Linux arm-linux-gnueabi")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-fs-linux-gnueabi)
	else()
		message("Linux desktop version")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
	endif()
	set(EXTERNAL_LIBS	-lpthread)
endif()


add_definitions(-DHOME=$ENV{HOME})

set(UI_VERSION_MAJOR 1)
set(UI_VERSION_MINOR 0)
set(UI_VERSION_PATCH 0)
set(UI_VERSION ${UI_VERSION_MAJOR}.${UI_VERSION_MINOR}.${UI_VERSION_PATCH})

# Force default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
		"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif()

add_definitions(-DVIRTUAL_MOCK=)

add_definitions(-DUI_VERSION_MAJOR=${UI_VERSION_MAJOR})
add_definitions(-DUI_VERSION_MINOR=${UI_VERSION_MINOR})
add_definitions(-DUI_VERSION_PATCH=${UI_VERSION_PATCH})
add_definitions(-DUI_VERSION_STR="${UI_VERSION}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Enablig debug flag")
	add_definitions(-DDEBUG)
endif()

set(SOURCES)
set(HEADERS)

SET (INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LIB_PREFIX}/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/ui/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/ui/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/core ${CMAKE_BINARY_DIR}/core)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})
set(INCLUDES
	${PROJECT_SOURCE_DIR}/core/include
	${PROJECT_SOURCE_DIR}/network/include
	${PROJECT_SOURCE_DIR}/printers/include
	${LIB_PREFIX}/include
	${INCLUDES}
)

include_directories(${INCLUDES})

# Next lines needed for building all Qt projects
find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories( ${CMAKE_BINARY_DIR} )


# using Qt meta-system (precompiler)
QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${HEADERS} )

###########################
## Install targets
###########################

link_directories(
	${CMAKE_BINARY_DIR}/core
	${CMAKE_BINARY_DIR}/network
	${CMAKE_BINARY_DIR}/printers/tij
	)

# compile
if (WIN32)
	add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
elseif(UNIX)
	add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${RES_SOURCES} ${UI_HEADERS} )
endif()
# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${QT_LIBRARIES} MComms MNetwork TijLibrary)
