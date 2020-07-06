##########################
#   MProtocol Includes   #
##########################
set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommandsfactory.h
	${CMAKE_CURRENT_SOURCE_DIR}/mcommands.h
	${CMAKE_CURRENT_SOURCE_DIR}/mconfigbase.h
	${CMAKE_CURRENT_SOURCE_DIR}/mconfig.h
	${CMAKE_CURRENT_SOURCE_DIR}/mfiles.h
	${CMAKE_CURRENT_SOURCE_DIR}/mlive.h
	${CMAKE_CURRENT_SOURCE_DIR}/merrorslogs.h
	${CMAKE_CURRENT_SOURCE_DIR}/mmessagevalues.h
	${CMAKE_CURRENT_SOURCE_DIR}/mcurrentmessage.h
	${CMAKE_CURRENT_SOURCE_DIR}/mprotocol.h
	${CMAKE_CURRENT_SOURCE_DIR}/mstatus.h
	${CMAKE_CURRENT_SOURCE_DIR}/mupdate.h
	PARENT_SCOPE
	)
