#############################################
#	Printers data structures and protocols  #
#############################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(JET_LIBRARY_NAME JetPrinter)

project(${JET_LIBRARY_NAME})
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

message("Parsing " ${JET_LIBRARY_NAME} " definitions")
message("PROJECT_NAME: " ${PROJECT_NAME})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})
message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/../../toolchain/cmake/macsa.cmake)	#configuration for macsa printers projects
include(${CMAKE_CURRENT_SOURCE_DIR}/../../toolchain/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration

if (WIN32)
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						${LIB_PREFIX}/lib/tinyxml2.lib)
elseif(UNIX)
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						${LIB_PREFIX}/lib/libtinyxml2.a)
endif()

#####################  VERSION DEFINITION  #############################
set(JET_LIBRARY_VERSION_MAJOR 1)
set(JET_LIBRARY_VERSION_MINOR 0)
set(JET_LIBRARY_VERSION_PATCH 0)
set(JET_LIBRARY_VERSION ${JET_LIBRARY_VERSION_MAJOR}.${JET_LIBRARY_VERSION_MINOR}.${JET_LIBRARY_VERSION_PATCH})

add_definitions(-DJET_LIBRARY_VERSION_MAJOR=${JET_LIBRARY_VERSION_MAJOR})
add_definitions(-DJET_LIBRARY_VERSION_MINOR=${JET_LIBRARY_VERSION_MINOR})
add_definitions(-DJET_LIBRARY_VERSION_PATCH=${JET_LIBRARY_VERSION_PATCH})
add_definitions(-DJET_LIBRARY_VERSION_STR="${JET_LIBRARY_VERSION}")

####################  SOURCES AND HEADERS  #############################

set(PRINTERS_SOURCES)
set(PRINTERS_HEADERS)
set(PRINTERS_INCLUDES)

set(JET_PROTOCOL_SOURCES)
set(JET_PROTOCOL_HEADERS)

set(JET_SOURCES)
set(JET_HEADERS)

set(LABELS_SOURCES)
set(LABELS_HEADERS)

## Enable labels
set(NISX_LABELS	true)

if (${ENABLE_TESTS})
	set(SRC_TEST)
	set(HDRS_TEST)
endif()

SET (PRINTERS_INCLUDES
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/jet/src
	${PROJECT_SOURCE_DIR}/jet/include
	${LIB_PREFIX}/include
)

include_directories(${PRINTERS_INCLUDES})

add_subdirectory(${PROJECT_SOURCE_DIR}/src         ${PROJECT_BINARY_DIR}/printers/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/include     ${PROJECT_BINARY_DIR}/printers/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/jetprotocol ${PROJECT_BINARY_DIR}/jetprotocol)
add_subdirectory(${PROJECT_SOURCE_DIR}/jet/src     ${PROJECT_BINARY_DIR}/jet/src)
add_subdirectory(${PROJECT_SOURCE_DIR}/jet/include ${PROJECT_BINARY_DIR}/jet/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/labels      ${PROJECT_BINARY_DIR}/labels)

if (${ENABLE_TESTS})
	set(SRC_TEST ${SRC_TEST})
	set(HDRS_TEST ${HDRS_TEST})
endif()

######################################
##			Targets					##
######################################
#######		JET Libraries		######
if (${BUILD_SHARED_LIBS} OR ${BUILD_STATIC_LIBS})
	message("lib" ${PROJECT_NAME} " creating targets")
	set(SOVERSION ${JET_LIBRARY_VERSION})

	if (${BUILD_SHARED_LIBS})
		add_library(${PROJECT_NAME} SHARED
							${JET_SOURCES} ${JET_HEADERS}
							${PRINTERS_SOURCES} ${PRINTERS_HEADERS}
							${PROTOCOL_SOURCES} ${PROTOCOL_HEADERS}
							${LABELS_SOURCES} ${LABELS_HEADERS})

		set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${SOVERSION})
		target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
		install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${LIB_PREFIX}/lib)
	endif()


	if (${BUILD_STATIC_LIBS})
		add_library(${PROJECT_NAME}-static STATIC
						${JET_SOURCES} ${JET_HEADERS}
						${PRINTERS_SOURCES} ${PRINTERS_HEADERS}
						${PROTOCOL_SOURCES} ${PROTOCOL_HEADERS}
						${LABELS_SOURCES} ${LABELS_HEADERS})
		set_target_properties(${PROJECT_NAME}-static PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})
		target_link_libraries(${PROJECT_NAME}-static ${EXTERNAL_LIBS})
		install(TARGETS ${PROJECT_NAME}-static LIBRARY DESTINATION ${LIB_PREFIX}/lib)
	endif()


	if (${ENABLE_TESTS} AND SRC_TEST)
		set(PROJECT_TEST_NAME ${PROJECT_NAME}_Test)
		link_directories(${PROJECT_BINARY_DIR}/jet)
		add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
		target_link_libraries(${PROJECT_TEST_NAME} ${EXTERNAL_LIBS})
		add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})

	endif()
endif()
