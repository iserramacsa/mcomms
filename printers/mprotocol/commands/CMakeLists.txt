##########################
#	Protocol Commands	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(PROTOCOL_SOURCES ${PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommands.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mconfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mfiles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mlive.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mstatus.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/mupdate.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mtools.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mboard.cpp
	PARENT_SCOPE
)

set(PROTOCOL_HEADERS ${PROTOCOL_HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/mtools.h
	${CMAKE_CURRENT_SOURCE_DIR}/mboard.h
	${HEADERS_LIB}
	PARENT_SCOPE
)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
