##########################
#	 Protocol Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

if (CLIENT)
	add_definitions(-DMCLIENT)
endif()

if (SERVER)
	add_definitions(-DMSERVER)
endif()

set(PROTOCOL_SOURCES ${PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommandsfactory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mprotocol.cpp
)

set(PROTOCOL_HEADERS ${PROTOCOL_HEADERS}
)

include_directories(commands)
add_subdirectory(commands)


set(PROTOCOL_SOURCES ${PROTOCOL_SOURCES}
	PARENT_SCOPE
	)

set(PROTOCOL_HEADERS ${PROTOCOL_HEADERS}
	PARENT_SCOPE
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
