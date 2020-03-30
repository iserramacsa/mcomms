##########################
#	 Protocol Sources	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

include_directories(commands)
add_subdirectory(commands)

set(JET_PROTOCOL_SOURCES ${JET_PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommandsfactory.cpp
	PARENT_SCOPE
)

set(JET_PROTOCOL_HEADERS ${JET_PROTOCOL_HEADERS}
	PARENT_SCOPE
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
