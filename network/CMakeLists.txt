##########################################
##	Macsa Network library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(NETWORK_LIB_NAME MNetwork)

project(${NETWORK_LIB_NAME})
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/macsa.cmake)	#configuration for macsa tij projects
include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration

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

SET (LIB_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LIB_PREFIX}/include
	)

include_directories(${LIB_INCLUDES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/network/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/network/include)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})

if (${ENABLE_TESTS})
    set(SRC_TEST ${SRC_TEST})
    set(HDRS_TEST ${HDRS_TEST})
endif()

###########################
## Install targets
###########################
set(SOVERSION ${NETWORK_LIB_VERSION})
if (${BUILD_SHARED_LIBS})
	add_library(${NETWORK_LIB_NAME} SHARED ${SOURCES} ${HEADERS})
	set_target_properties(${NETWORK_LIB_NAME}
		PROPERTIES SOVERSION ${SOVERSION})
endif()

if (${BUILD_STATIC_LIBS})
	add_library(${NETWORK_LIB_NAME}-static STATIC ${SOURCES} ${HEADERS})
	set_target_properties(${NETWORK_LIB_NAME}-static
			PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${NETWORK_LIB_NAME})
endif()

target_link_libraries(${NETWORK_LIB_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${NETWORK_LIB_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)


if (${ENABLE_TESTS})
	set(PROJECT_TEST_NAME ${NETWORK_LIB_NAME}_Test)
	link_directories(
	    ${CMAKE_BINARY_DIR}/network
	)

	add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
	target_link_libraries(${PROJECT_TEST_NAME} ${EXTERNAL_LIBS} MNetwork)
	add_test(${NETWORK_LIB_NAME} ${PROJECT_TEST_NAME})

endif()
