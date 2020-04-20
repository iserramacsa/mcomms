## Project configuration

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")
set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")

option(BUILD_STATIC_LIBS "Build the static library" ON)
option(BUILD_SHARED_LIBS "Build the shared library" ON)

add_definitions(-DHOME=$ENV{HOME})

if (WIN32)
	message("Windows version: " ${CMAKE_CXX_COMPILER})
	set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
elseif(UNIX)
	message("Linux version: " ${CMAKE_CXX_COMPILER})
	add_compile_options(-fPIC)
	if (CMAKE_CXX_COMPILER MATCHES "gnueabihf")
		set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
		set(CMAKE_FIND_ROOT_PATH ${HOME}/engicam-loco-10/buildroot/output/staging)
		add_definitions(-DLOCO)
		message("Linux arm-gnueabihf")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-linux-gnueabihf)
	elseif(CMAKE_CXX_COMPILER MATCHES "gnueabi")
		set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
		set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
		set(CMAKE_FIND_ROOT_PATH ${HOME}/engicam-loco-10/buildroot/output/staging)
		message("Linux arm-linux-gnueabi")
		add_definitions(-DARMSTONE_A9)
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-fs-linux-gnueabi)
	else()
		set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
		set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
		set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
		message("Linux desktop version")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
	endif()
endif()

# Force default build type to Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
		"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	message("Building release mode")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	message("Enablig debug flag")
	add_definitions(-DDEBUG)
endif()

