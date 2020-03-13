##########################
#	Protocol Commands	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(PROTOCOL_SOURCES ${PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommands.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfigbase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetcounters.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetfiles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetlogs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessages.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessagevalues.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetstatus.cpp

	PARENT_SCOPE
)

set(PROTOCOL_HEADERS ${PROTOCOL_HEADERS}
	${HEADERS_LIB}
	PARENT_SCOPE
)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
