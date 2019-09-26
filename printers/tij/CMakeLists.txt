#############################################
#	Printers data structures and protocols  #
#############################################
## Project configuration
cmake_minimum_required(VERSION 3.5)

set(TIJ_LIBRARY_NAME TijLibrary)

if (NOT PROJECT_NAME)
	project(${TIJ_LIBRARY_NAME})
	set(STANDALONE)

	set (CMAKE_CXX_STANDARD 11)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")
	set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unused-parameter -g2 -pedantic")

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

	endif()

	add_definitions(-DVIRTUAL_MOCK=)
	add_definitions(-DHOME=$ENV{HOME})
else()
	if (WIN32)
		set(EXTERNALS	${LIB_PREFIX}/lib/tinyxml2.lib)
	elseif(UNIX)
		set(EXTERNALS	${LIB_PREFIX}/lib/libtinyxml2.a)
	endif()
endif()


#####################  VERSION DEFINITION  #############################
set(TIJ_LIBRARY_VERSION_MAJOR 1)
set(TIJ_LIBRARY_VERSION_MINOR 0)
set(TIJ_LIBRARY_VERSION_PATCH 0)
set(TIJ_LIBRARY_VERSION ${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH})

add_definitions(-DMCLIENT)
####################  SOURCES AND HEADERS  #############################
set(PRINTERS_SOURCES)
set(PRINTERS_HEADERS)
set(PRINTERS_INCLUDES)
set(PROTOCOL_SOURCES)
set(PROTOCOL_HEADERS)
set(TIJ_SOURCES)
set(TIJ_HEADERS)

SET (PRINTERS_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${LIB_PREFIX}/include
)

include_directories(${PRINTERS_INCLUDES})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../src ${CMAKE_BINARY_DIR}/printers/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_BINARY_DIR}/printers/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../mprotocol ${CMAKE_BINARY_DIR}/mprotocol)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/tij/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/tij/include)

######################################
##			Targets					##
######################################
if (NOT INCLUDE_TESTS)

	#######		TIJ Libraries		######
	message("lib" ${TIJ_LIBRARY_NAME} " definition")
	set(SOVERSION ${TIJ_LIBRARY_VERSION})
	add_library(${TIJ_LIBRARY_NAME} SHARED  ${TIJ_SOURCES} ${PRINTERS_SOURCES} ${PROTOCOL_SOURCES} ${TIJ_SOURCES}
											${TIJ_HEADERS} ${PRINTERS_HEADERS} ${PROTOCOL_HEADERS} ${TIJ_HEADERS})
	add_library(${TIJ_LIBRARY_NAME}-static STATIC ${TIJ_SOURCES} ${PRINTERS_SOURCES} ${PROTOCOL_SOURCES} ${TIJ_SOURCES}
												  ${TIJ_HEADERS} ${PRINTERS_HEADERS} ${PROTOCOL_HEADERS} ${TIJ_HEADERS})
	set_target_properties(${TIJ_LIBRARY_NAME}
		PROPERTIES SOVERSION ${SOVERSION})

	set_target_properties(${TIJ_LIBRARY_NAME}-static
			PROPERTIES SOVERSION ${SOVERSION} OUTPUT_NAME ${TIJ_LIBRARY_NAME})

	target_link_libraries(${TIJ_LIBRARY_NAME} ${EXTERNALS})
	install(TARGETS ${TIJ_LIBRARY_NAME}
		LIBRARY DESTINATION ${LIB_PREFIX}/lib)
else()

	set(EXTERNAL_LIBS	${EXTERNAL_LIBS} ${EXTERNALS}	PARENT_SCOPE)

	set(SOURCES			${SOURCES}
						${PRINTERS_SOURCES}
						${PROTOCOL_SOURCES}
						${TIJ_SOURCES}
						PARENT_SCOPE)

	set(HEADERS			${HEADERS}
						${PRINTERS_HEADERS}
						${PROTOCOL_HEADERS}
						${TIJ_HEADERS}
						PARENT_SCOPE)
endif()

if (NOT ${PROJECT_NAME} STREQUAL ${TIJ_LIBRARY_NAME})
	SET (INCLUDES ${INCLUDES}
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/../include
		PARENT_SCOPE)
endif()
