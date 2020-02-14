#############################################
#	Printers data structures and protocols  #
#############################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(TIJ_LIBRARY_NAME TijLibrary)

project(${TIJ_LIBRARY_NAME})
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)


include(${CMAKE_CURRENT_SOURCE_DIR}/../../toolchain/cmake/macsa.cmake)	#configuration for macsa tij projects
include(${CMAKE_CURRENT_SOURCE_DIR}/../../toolchain/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration

#include($ENV{HOME}/workspace/tools/cmake/macsa.cmake)

if (WIN32)
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						${LIB_PREFIX}/lib/tinyxml2.lib)
elseif(UNIX)
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						${LIB_PREFIX}/lib/libtinyxml2.a)
endif()

#####################  VERSION DEFINITION  #############################
set(TIJ_LIBRARY_VERSION_MAJOR 1)
set(TIJ_LIBRARY_VERSION_MINOR 0)
set(TIJ_LIBRARY_VERSION_PATCH 0)
set(TIJ_LIBRARY_VERSION ${TIJ_LIBRARY_VERSION_MAJOR}.${TIJ_LIBRARY_VERSION_MINOR}.${TIJ_LIBRARY_VERSION_PATCH})

####################  SOURCES AND HEADERS  #############################

set(PRINTERS_SOURCES)
set(PRINTERS_HEADERS)
set(PRINTERS_INCLUDES)

set(PROTOCOL_SOURCES)
set(PROTOCOL_HEADERS)

set(TIJ_SOURCES)
set(TIJ_HEADERS)

set(LABELS_SOURCES)
set(LABELS_HEADERS)

## Enable labels
set(NISX_LABELS	true)

SET (PRINTERS_INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/tij/src
	${PROJECT_SOURCE_DIR}/tij/include
	${LIB_PREFIX}/include
)

include_directories(${PRINTERS_INCLUDES})

add_subdirectory(${PROJECT_SOURCE_DIR}/src         ${CMAKE_BINARY_DIR}/printers/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include     ${CMAKE_BINARY_DIR}/printers/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/mprotocol   ${CMAKE_BINARY_DIR}/mprotocol)
add_subdirectory(${PROJECT_SOURCE_DIR}/tij/src     ${CMAKE_BINARY_DIR}/tij/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/tij/include ${CMAKE_BINARY_DIR}/tij/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/labels      ${CMAKE_BINARY_DIR}/labels)

######################################
##			Targets					##
######################################
#######		TIJ Libraries		######
message("lib" ${TIJ_LIBRARY_NAME} " definition")
set(SOVERSION ${TIJ_LIBRARY_VERSION})
add_library(${TIJ_LIBRARY_NAME} SHARED  ${TIJ_SOURCES} ${PRINTERS_SOURCES} ${PROTOCOL_SOURCES} ${TIJ_SOURCES} ${LABELS_SOURCES}
										${TIJ_HEADERS} ${PRINTERS_HEADERS} ${PROTOCOL_HEADERS} ${TIJ_HEADERS} ${LABELS_HEADERS})
add_library(${TIJ_LIBRARY_NAME}-static STATIC ${TIJ_SOURCES} ${PRINTERS_SOURCES} ${PROTOCOL_SOURCES} ${TIJ_SOURCES} ${LABELS_SOURCES}
											  ${TIJ_HEADERS} ${PRINTERS_HEADERS} ${PROTOCOL_HEADERS} ${TIJ_HEADERS} ${LABELS_HEADERS})
set_target_properties(${TIJ_LIBRARY_NAME}
	PROPERTIES SOVERSION ${SOVERSION})

set_target_properties(${TIJ_LIBRARY_NAME}-static
		PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${TIJ_LIBRARY_NAME})

target_link_libraries(${TIJ_LIBRARY_NAME} ${EXTERNAL_LIBS})
install(TARGETS ${TIJ_LIBRARY_NAME}
	LIBRARY DESTINATION ${LIB_PREFIX}/lib)
