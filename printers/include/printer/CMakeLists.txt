##############################
#   Macsa Printer Includes   #
##############################

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/board.h
	${CMAKE_CURRENT_SOURCE_DIR}/cartridge.h
	${CMAKE_CURRENT_SOURCE_DIR}/comms.h
	${CMAKE_CURRENT_SOURCE_DIR}/configuration.h
	${CMAKE_CURRENT_SOURCE_DIR}/datatypes.h
	${CMAKE_CURRENT_SOURCE_DIR}/datecodes.h
	${CMAKE_CURRENT_SOURCE_DIR}/encoder.h
	${CMAKE_CURRENT_SOURCE_DIR}/errors.h
	${CMAKE_CURRENT_SOURCE_DIR}/files.h
	${CMAKE_CURRENT_SOURCE_DIR}/ifilesmanager.h
	${CMAKE_CURRENT_SOURCE_DIR}/inputs.h
	${CMAKE_CURRENT_SOURCE_DIR}/iobase.h
	${CMAKE_CURRENT_SOURCE_DIR}/messagemanager.h
	${CMAKE_CURRENT_SOURCE_DIR}/outputs.h
	${CMAKE_CURRENT_SOURCE_DIR}/printer.h
	${CMAKE_CURRENT_SOURCE_DIR}/shotmode.h
	${CMAKE_CURRENT_SOURCE_DIR}/status.h
	PARENT_SCOPE
	)
