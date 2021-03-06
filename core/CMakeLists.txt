##########################################
##	Macsa Communications library
##########################################
## Project configuration
cmake_minimum_required(VERSION 3.5.0)

set(PROJECT_NAME MComms)
project(${PROJECT_NAME})

message("Parsing " ${PROJECT_NAME} " definitions")
message("PROJECT_NAME: " ${PROJECT_NAME})
message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})
message("PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR})

set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/macsa.cmake)	#configuration for macsa magnetiq projects
include(${CMAKE_CURRENT_SOURCE_DIR}/../toolchain/cmake/test.cmake)  #configuration test enabled and GTest requiered configuration
set (UTILS_DIR	${CMAKE_CURRENT_SOURCE_DIR}/../utils)


option(INCLUDE_TIJ_LIBS "Add Tij library" ON)
option(INCLUDE_JET_LIBS "Add Jet library" ON)

if(UNIX)
	if (${BUILD_SHARED_LIBS})
		add_compile_options(-fPIC)
	endif()
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
						-lpthread)
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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src	 ${PROJECT_BINARY_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/../network	 ${PROJECT_BINARY_DIR}/network)
## Add printers ##
add_subdirectory(${PROJECT_SOURCE_DIR}/../printers	 ${PROJECT_BINARY_DIR}/printers)


SET (INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/../network/include
	${PROJECT_SOURCE_DIR}/../printers/include
	${LIB_PREFIX}/include
	${UTILS_DIR}/include
	${INCLUDES}
)

set(SOURCES ${SOURCES})
set(HEADERS ${HEADERS})

include_directories(${INCLUDES})

if (${ENABLE_TESTS})
	set(SRC_TEST ${SRC_TEST})
	set(HDRS_TEST ${HDRS_TEST})
endif()

###########################
## Install targets
###########################
if (${BUILD_SHARED_LIBS} OR ${BUILD_STATIC_LIBS})
	message("lib" ${PROJECT_NAME} " creating targets")
	set(SOVERSION ${MCOMMS_CORE_VERSION})

	link_directories(
		${PROJECT_BINARY_DIR}/network
	)
	set(TARGET_LINK_LIBS
		${PROJECT_BINARY_DIR}/network/libMNetwork.a
		)
	if (${INCLUDE_TIJ_LIBS})
		link_directories(
			${PROJECT_BINARY_DIR}/printers/tij
		)
		set(TARGET_LINK_LIBS ${TARGET_LINK_LIBS}
			${PROJECT_BINARY_DIR}/../printers/tij/libTijPrinter.a
			)
		endif()
	if (${INCLUDE_JET_LIBS})
		link_directories(
			${PROJECT_BINARY_DIR}/printers/jet
		)
		set(TARGET_LINK_LIBS ${TARGET_LINK_LIBS}
			${PROJECT_BINARY_DIR}/../printers/jet/libJetPrinter.a
			)
	endif()


	if (${BUILD_SHARED_LIBS})
		add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
		set_target_properties(${PROJECT_NAME}
			PROPERTIES SOVERSION ${SOVERSION})
		target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBS})
		install(TARGETS ${PROJECT_NAME}
			LIBRARY DESTINATION ${LIB_PREFIX}/lib)
	endif()


	if (${BUILD_STATIC_LIBS})
		add_library(${PROJECT_NAME}-static STATIC ${SOURCES} ${HEADERS})
		set_target_properties(${PROJECT_NAME}-static
				PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${PROJECT_NAME})
		target_link_libraries(${PROJECT_NAME}-static  ${EXTERNAL_LIBS} ${TARGET_LINK_LIBS})
		install(TARGETS ${PROJECT_NAME}-static
			LIBRARY DESTINATION ${LIB_PREFIX}/lib)
	endif()


	if (${ENABLE_TESTS} AND SRC_TEST)
		set(PROJECT_TEST_NAME ${PROJECT_NAME}CoreTest)
#		link_directories(${PROJECT_BINARY_DIR}
#			${PROJECT_BINARY_DIR}/network
#			${PROJECT_BINARY_DIR}/printers/tij
#			${PROJECT_BINARY_DIR}/printers/jet
#			)
		add_executable(${PROJECT_TEST_NAME} ${SRC_TEST} ${HDRS_TEST})
		target_link_libraries(${PROJECT_TEST_NAME} ${EXTERNAL_LIBS} MComms MNetwork TijPrinter JetPrinter)
		add_test(${PROJECT_NAME} ${PROJECT_TEST_NAME})

	endif()
endif()
