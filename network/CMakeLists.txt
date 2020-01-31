##########################################
##	Macsa Network library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(NETWORK_LIB_NAME MNetwork)

project(${NETWORK_LIB_NAME})

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")
set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2")

if (WIN32)
	set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
elseif(UNIX)
	message("Linux version: " CMAKE_CXX_COMPILER)
	if (CMAKE_CXX_COMPILER MATCHES "gnueabihf")
		message("gnueabihf variant")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-linux-gnueabihf)
	elseif(CMAKE_CXX_COMPILER MATCHES "gnueabi")
		message("gnueabi variant")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-buildroot-linux-gnueabi)
                add_definitions(-Dnullptr=0)
	else()
		message("Linux desktop version")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
	endif()
	set(EXTERNAL_LIBS	-pthread)
endif()

if (NOT INCLUDE_TESTS)
    add_definitions(-DVIRTUAL_MOCK=)
endif()
add_definitions(-DHOME=$ENV{HOME})



set(NETWORK_LIB_VERSION_MAJOR 1)
set(NETWORK_LIB_VERSION_MINOR 0)
set(NETWORK_LIB_VERSION_PATCH 0)
set(NETWORK_LIB_VERSION ${NETWORK_LIB_VERSION_MAJOR}.${NETWORK_LIB_VERSION_MINOR}.${NETWORK_LIB_VERSION_PATCH})

#add_definitions(-DDEBUG)
add_definitions(-DNETWORK_VERSION_MAJOR=${NETWORK_LIB_VERSION_MAJOR})
add_definitions(-DNETWORK_VERSION_MINOR=${NETWORK_LIB_VERSION_MINOR})
add_definitions(-DNETWORK_VERSION_PATCH=${NETWORK_LIB_VERSION_PATCH})
add_definitions(-DNETWORK_VERSION_STR="${NETWORK_LIB_VERSION}")

set(_SRCS)
set(_HDRS)

SET (LIB_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LIB_PREFIX}/include
	)

include_directories(${LIB_INCLUDES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/network/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/network/include)

set(_SRCS ${_SRCS}
)
set(_HDRS ${_HDRS}
)

if(INCLUDE_TESTS)
    set(SRC_TEST ${SRC_TEST}
        PARENT_SCOPE
    )
    set(HDRS_TEST ${HDRS_TEST}
        PARENT_SCOPE
    )
endif()
###########################
## Install targets
###########################
set(SOVERSION ${NETWORK_LIB_VERSION})
add_library(${NETWORK_LIB_NAME} SHARED ${_SRCS} ${_HDRS})
add_library(${NETWORK_LIB_NAME}-static STATIC ${_SRCS} ${_HDRS})
set_target_properties(${NETWORK_LIB_NAME}
	PROPERTIES SOVERSION ${SOVERSION})

set_target_properties(${NETWORK_LIB_NAME}-static
		PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${NETWORK_LIB_NAME})

target_link_libraries(${NETWORK_LIB_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${NETWORK_LIB_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)

