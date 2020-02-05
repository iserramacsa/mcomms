##########################
#	 MCommsUI Headers	 #
##########################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)


set(MOC_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerslistmodel.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerconndialog.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerview.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerstatusview.h
	${CMAKE_CURRENT_SOURCE_DIR}/printerfilesview.h
	)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/viewers)

set(HEADERS ${MOC_HEADERS}
	PARENT_SCOPE
	)

