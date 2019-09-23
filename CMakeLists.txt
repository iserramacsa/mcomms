##########################################
##	Macsa Communications library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME MComms)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

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
		message("Linux arm-gnueabi")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-buildroot-linux-gnueabi)
	else()
		message("Linux desktop version")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
	endif()
endif()


add_definitions(-DHOME=$ENV{HOME})
set(EXTERNAL_LIBS	-pthread)

set(LIBRARY_VERSION_MAJOR 1)
set(LIBRARY_VERSION_MINOR 0)
set(LIBRARY_VERSION_PATCH 0)
set(LIBRARY_VERSION ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})

# Force default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
		"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif()

add_definitions(-DVIRTUAL_MOCK=)

add_definitions(-DVERSION_MAJOR=${LIBRARY_VERSION_MAJOR})
add_definitions(-DVERSION_MINOR=${LIBRARY_VERSION_MINOR})
add_definitions(-DVERSION_PATCH=${LIBRARY_VERSION_PATCH})
add_definitions(-DVERSION_STR="${LIBRARY_VERSION}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Enablig debug flag")
	add_definitions(-DDEBUG)
endif()


set(SOURCES)
set(HEADERS)

SET (INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${LIB_PREFIX}/include
	)

add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/network ${CMAKE_BINARY_DIR}/network)
##Add printers
add_subdirectory(${PROJECT_SOURCE_DIR}/printers ${CMAKE_BINARY_DIR}/printers)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})
SET (INCLUDES ${INCLUDES})

include_directories(${INCLUDES})

###########################
## Install targets
###########################
set(SOVERSION ${LIBRARY_VERSION})
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME}
	PROPERTIES SOVERSION ${SOVERSION})

set_target_properties(${PROJECT_NAME}-static
		PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)

