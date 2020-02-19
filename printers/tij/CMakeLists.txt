#############################################
#	Printers data structures and protocols  #
#############################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(TIJ_LIBRARY_NAME TijLibrary)

project(${TIJ_LIBRARY_NAME})
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

message("Parsing " ${TIJ_LIBRARY_NAME} " definitions")
message("PROJECT_NAME: " ${PROJECT_NAME})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

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

add_subdirectory(${PROJECT_SOURCE_DIR}/src         ${PROJECT_BINARY_DIR}/printers/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include     ${PROJECT_BINARY_DIR}/printers/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/mprotocol   ${PROJECT_BINARY_DIR}/mprotocol)
add_subdirectory(${PROJECT_SOURCE_DIR}/tij/src     ${PROJECT_BINARY_DIR}/tij/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/tij/include ${PROJECT_BINARY_DIR}/tij/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/labels      ${PROJECT_BINARY_DIR}/labels)

if (${ENABLE_TESTS})
	set(SRC_TEST ${SRC_TEST})
	set(HDRS_TEST ${HDRS_TEST})
endif()

######################################
##			Targets					##
######################################
#######		TIJ Libraries		######
if (${BUILD_SHARED_LIBS} OR ${BUILD_STATIC_LIBS})
	message("lib" ${PROJECT_NAME} " creating targets")
	set(SOVERSION ${TIJ_LIBRARY_VERSION})

	if (${BUILD_SHARED_LIBS})
		add_library(${PROJECT_NAME} SHARED
							${TIJ_SOURCES} ${TIJ_HEADERS}
							${PRINTERS_SOURCES} ${PRINTERS_HEADERS}
							${PROTOCOL_SOURCES} ${PROTOCOL_HEADERS}
							${LABELS_SOURCES} ${LABELS_HEADERS})

		set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${SOVERSION})
	endif()


	if (${BUILD_STATIC_LIBS})
		add_library(${PROJECT_NAME}-static STATIC
						${TIJ_SOURCES} ${TIJ_HEADERS}
						${PRINTERS_SOURCES} ${PRINTERS_HEADERS}
						${PROTOCOL_SOURCES} ${PROTOCOL_HEADERS}
						${LABELS_SOURCES} ${LABELS_HEADERS})
		set_target_properties(${PROJECT_NAME}-static PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})
	endif()

	target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
	install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${LIB_PREFIX}/lib)

	if (${ENABLE_TESTS} AND SRC_TEST)
		set(PROJECT_TEST_NAME ${PROJECT_NAME}_Test)
		link_directories(${PROJECT_BINARY_DIR}/tij)
		add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
		target_link_libraries(${PROJECT_TEST_NAME} ${EXTERNAL_LIBS})
		add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})

	endif()
endif()
