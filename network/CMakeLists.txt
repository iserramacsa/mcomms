##########################################
##	Macsa Network library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(NETWORK_LIB_NAME MNetwork)

project(${NETWORK_LIB_NAME})
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("Parsing " ${NETWORK_LIB_NAME} " definitions")
message("PROJECT_NAME: " ${PROJECT_NAME})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})


include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/macsa.cmake)	#configuration for macsa tij projects
include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration
#include(${CMAKE_CURRENT_SOURCE_DIR}/../utils/utils.cmake)	#configuration for macsa tij projects
#Enabling options
#set (ADD_OBSERVER_PATTERN ON)
set (UTILS_DIR	${CMAKE_CURRENT_SOURCE_DIR}/../utils)

if(UNIX)
	if (${BUILD_SHARED_LIBS})
		add_compile_options(-fPIC)
	endif()
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						-pthread)
endif()

set(NETWORK_LIB_VERSION_MAJOR 1)
set(NETWORK_LIB_VERSION_MINOR 0)
set(NETWORK_LIB_VERSION_PATCH 0)
set(NETWORK_LIB_VERSION ${NETWORK_LIB_VERSION_MAJOR}.${NETWORK_LIB_VERSION_MINOR}.${NETWORK_LIB_VERSION_PATCH})

#add_definitions(-DDEBUG)
add_definitions(-DNETWORK_VERSION_MAJOR=${NETWORK_LIB_VERSION_MAJOR})
add_definitions(-DNETWORK_VERSION_MINOR=${NETWORK_LIB_VERSION_MINOR})
add_definitions(-DNETWORK_VERSION_PATCH=${NETWORK_LIB_VERSION_PATCH})
add_definitions(-DNETWORK_VERSION_STR="${NETWORK_LIB_VERSION}")


set(SOURCES)
set(HEADERS)

if (${ENABLE_TESTS})
	set(SRC_TEST)
	set(HDRS_TEST)
endif()

SET (LIB_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${UTILS_DIR}/include
	${LIB_PREFIX}/include
	)

include_directories(${LIB_INCLUDES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src		${PROJECT_BINARY_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include	${PROJECT_BINARY_DIR}/include)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})

if (${ENABLE_TESTS})
    set(SRC_TEST ${SRC_TEST})
	set(HDRS_TEST ${HDRS_TEST})
endif()

###########################
## Install targets
###########################
if (${BUILD_SHARED_LIBS} OR ${BUILD_STATIC_LIBS})
	set(SOVERSION ${NETWORK_LIB_VERSION})
	message("lib" ${NETWORK_LIB_NAME} " creating targets")

	if (${BUILD_SHARED_LIBS})
		add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
		set_target_properties(${PROJECT_NAME}
			PROPERTIES SOVERSION ${SOVERSION})
	endif()

	if (${BUILD_STATIC_LIBS})
		add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
		set_target_properties(${PROJECT_NAME}-static
				PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})
	endif()

	target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
	install(TARGETS ${PROJECT_NAME}	LIBRARY DESTINATION ${LIB_PREFIX}/lib)


	if (${ENABLE_TESTS})
		message("Adding ${PROJECT_NAME} tests" )
		set(PROJECT_TEST_NAME ${PROJECT_NAME}Tests)
		link_directories(${PROJECT_BINARY_DIR})

		add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
		target_link_libraries(${PROJECT_TEST_NAME} ${EXTERNAL_LIBS} MNetwork)
		add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})
	endif()
endif()
