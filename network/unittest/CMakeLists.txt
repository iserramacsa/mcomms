##########################################
##	Macsa Netwrok library unit test
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME MNetwork_Unit_Test)
project(${PROJECT_NAME})

set (CMAKE_CXX_STANDARD 11)
set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

############################################################
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

############################################################
# GTest integration
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})
#include_directories("/usr/include")



if (WIN32)
	set (CMAKE_CXX_STANDARD 11)
	set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")
	set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
elseif(UNIX)
	##TODO add support for arm devices
	set (CMAKE_CXX_STANDARD 11)
	set (CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")
	set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
	#set(TINY_XML_LIB	${LIB_PREFIX}/lib/libtinyxml2.a)
	set(EXTERNAL_LIBS	GTest::GTest
						GTest::Main
						gmock
						gmock_main
						-pthread)
endif()

set(INCLUDE_TESTS true)

add_definitions(-DVIRTUAL_MOCK=virtual)
add_definitions(-DHOME=$ENV{HOME})
#add_definitions(-DDEBUG)

set(SOURCES)
set(HEADERS)

set(LIBRARY_VERSION 1.0.0)

SET (INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${GOOGLE_MOCK_DIR}/include
	${LIB_PREFIX}/include
	)

include_directories(${INCLUDES})

add_subdirectory(${PROJECT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

set(SOURCES ${SOURCES}
	main.cpp
)

set(HEADERS ${HEADERS}
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
