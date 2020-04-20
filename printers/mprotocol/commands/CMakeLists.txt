##########################
#	Protocol Commands	 #
##########################

if (INCLUDE_TESTS)
	add_subdirectory(test)
endif()

set(TIJ_PROTOCOL_SOURCES ${TIJ_PROTOCOL_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/mcommands.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mconfigbase.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mconfig.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mfiles.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mlive.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mstatus.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mmessagevalues.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mcurrentmessage.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/merrorslogs.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mupdate.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/mtools.cpp
	PARENT_SCOPE
)

set(TIJ_PROTOCOL_HEADERS ${TIJ_PROTOCOL_HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/mtools.h
	${HEADERS_LIB}
	PARENT_SCOPE
)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
