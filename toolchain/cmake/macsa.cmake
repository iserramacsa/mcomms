## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")
set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")

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


add_definitions(-DHOME=$ENV{HOME})
