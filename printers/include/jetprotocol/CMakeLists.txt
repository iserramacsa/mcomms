##########################
#  JetProtocol Includes  #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommand.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetcommandsfactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfigbase.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetconfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetcounters.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetfiles.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetlogs.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessages.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetmessagevalues.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetnisx.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetoutput.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetpause.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetprotocol.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetsingleconfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetsinglestatus.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetstatus.h
	${CMAKE_CURRENT_SOURCE_DIR}/jetversions.h


	PARENT_SCOPE
	)
