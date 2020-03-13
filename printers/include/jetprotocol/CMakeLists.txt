##########################
#  JetProtocol Includes  #
##########################

set(HEADERS_LIB
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommandsfactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommands.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfigbase.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetcounters.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetfiles.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetlogs.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessages.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessagevalues.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetprotocol.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetstatus.h

	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(_HDRS ${HDRS}
	${HEADERS_LIB}
	PARENT_SCOPE
	)
