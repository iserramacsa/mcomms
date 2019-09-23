##########################################
##	Macsa Network library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(LIBRARY_NAME MNetwork)

if (NOT PROJECT_NAME)
	set(PROJECT_NAME ${LIBRARY_NAME})
	project(${PROJECT_NAME})
	set(STANDALONE)

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
		else()
			message("Linux desktop version")
			set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/x64)
		endif()
		set(EXTERNAL_LIBS	-pthread)
	endif()

	add_definitions(-DVIRTUAL_MOCK=)
	add_definitions(-DHOME=$ENV{HOME})

endif()

set(LIBRARY_VERSION_MAJOR 1)
set(LIBRARY_VERSION_MINOR 0)
set(LIBRARY_VERSION_PATCH 0)
set(LIBRARY_VERSION ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})

#add_definitions(-DDEBUG)
add_definitions(-DNETWORK_VERSION_MAJOR=${LIBRARY_VERSION_MAJOR})
add_definitions(-DNETWORK_VERSION_MINOR=${LIBRARY_VERSION_MINOR})
add_definitions(-DNETWORK_VERSION_PATCH=${LIBRARY_VERSION_PATCH})
add_definitions(-DNETWORK_VERSION_STR="${LIBRARY_VERSION}")

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

###########################
## Install targets
###########################
if (NOT INCLUDE_TESTS)
set(SOVERSION ${LIBRARY_VERSION})
add_library(${LIBRARY_NAME} SHARED ${_SRCS} ${_HDRS})
add_library(${LIBRARY_NAME}-static STATIC ${_SRCS} ${_HDRS})
set_target_properties(${LIBRARY_NAME}
	PROPERTIES SOVERSION ${SOVERSION})

set_target_properties(${LIBRARY_NAME}-static
		PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${LIBRARY_NAME})

target_link_libraries(${LIBRARY_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${LIBRARY_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)
endif()

if (NOT STANDALONE)
	SET (INCLUDES ${INCLUDES}
		${CMAKE_CURRENT_SOURCE_DIR}/include
		PARENT_SCOPE)
	if (INCLUDE_TESTS)
		set(SOURCES ${SOURCES}
			${_SRCS}
			PARENT_SCOPE
		)
		set(HEADERS ${HEADERS}
			${_HDRS}
			PARENT_SCOPE
		)
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}	PARENT_SCOPE)
	endif()
endif()
