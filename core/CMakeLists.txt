##########################################
##	Macsa Communications library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME MComms)
project(${PROJECT_NAME})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#include($ENV{HOME}/workspace/tools/cmake/macsa.cmake)

if(UNIX)
	add_compile_options(-fPIC)
	set(EXTERNAL_LIBS	-lpthread)
endif()

if (NOT VIRTUAL_MOCK)
	add_definitions(-DVIRTUAL_MOCK=)
endif()


set(MCOMMS_CORE_VERSION_MAJOR 1)
set(MCOMMS_CORE_VERSION_MINOR 0)
set(MCOMMS_CORE_VERSION_PATCH 0)
set(MCOMMS_CORE_VERSION ${MCOMMS_CORE_VERSION_MAJOR}.${MCOMMS_CORE_VERSION_MINOR}.${MCOMMS_CORE_VERSION_PATCH})


add_definitions(-DCORE_VERSION_MAJOR=${MCOMMS_CORE_VERSION_MAJOR})
add_definitions(-DCORE_VERSION_MINOR=${MCOMMS_CORE_VERSION_MINOR})
add_definitions(-DCORE_VERSION_PATCH=${MCOMMS_CORE_VERSION_PATCH})
add_definitions(-DCORE_VERSION_STR="${MCOMMS_CORE_VERSION}")


set(SOURCES)
set(HEADERS)
set(INCLUDES)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/core/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/core/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/../network ${CMAKE_BINARY_DIR}/network)
## Add printers ##
add_subdirectory(${PROJECT_SOURCE_DIR}/../printers ${CMAKE_BINARY_DIR}/printers)


SET (INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/../network/include
	${PROJECT_SOURCE_DIR}/../printers/include
	${LIB_PREFIX}/include
	${INCLUDES}
)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})


include_directories(${INCLUDES})

###########################
## Install targets
###########################
set(SOVERSION ${MCOMMS_CORE_VERSION})
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME}
	PROPERTIES SOVERSION ${SOVERSION})

set_target_properties(${PROJECT_NAME}-static
		PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})

link_directories(
	${CMAKE_BINARY_DIR}/network
	${CMAKE_BINARY_DIR}/printers/tij
)

target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)
