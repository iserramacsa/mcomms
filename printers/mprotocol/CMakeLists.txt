##########################
#	 Protocol Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(TIJ_PROTOCOL_SOURCES ${TIJ_PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommandsfactory.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/mprotocol.cpp
)

set(TIJ_PROTOCOL_HEADERS ${TIJ_PROTOCOL_HEADERS}
)

include_directories(commands)
add_subdirectory(commands)


set(TIJ_PROTOCOL_SOURCES ${TIJ_PROTOCOL_SOURCES}
	PARENT_SCOPE
	)

set(TIJ_PROTOCOL_HEADERS ${TIJ_PROTOCOL_HEADERS}
	PARENT_SCOPE
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
