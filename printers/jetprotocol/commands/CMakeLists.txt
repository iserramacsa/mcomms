##########################
#	Protocol Commands	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(JET_PROTOCOL_SOURCES ${JET_PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommand.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfigbase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetcounters.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetfiles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetlogs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessages.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessagevalues.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetnisx.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetoutput.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetpause.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetsingleconfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetsinglestatus.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetstatus.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetversions.cpp

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
