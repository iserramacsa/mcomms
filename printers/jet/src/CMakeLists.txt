##########################
#  Jet Printer sources   #
##########################

set(JET_SOURCES ${JET_SOURCES}
	${CMAKE_CURRENT_SOURCE_DIR}/jetprinter.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetcomms.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetboard.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetio.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/jetlog.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/messagemanager.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/printhead.cpp
	PARENT_SCOPE
	)

set(JET_HEADERS ${JET_HEADERS}
	PARENT_SCOPE
	)
