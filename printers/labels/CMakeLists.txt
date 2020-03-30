##########################
#     Labels Sources     #
##########################

set(LABELS_SOURCES ${LABELS_SOURCES}
)

set(LABELS_HEADERS ${LABELS_HEADERS}
)

## LABEL FORMAT SELECTOR (NisX, Zeta, ...)
if (NISX_LABELS)
	include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/nisx)
	if(TIJ)
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nisx ${CMAKE_BINARY_DIR}/tij/nisx)
	elseif(JET)
		add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/nisx ${CMAKE_BINARY_DIR}/jet/nisx)
	endif()
endif()

set(LABELS_SOURCES ${LABELS_SOURCES}
	PARENT_SCOPE
	)

set(LABELS_HEADERS ${LABELS_HEADERS}
	PARENT_SCOPE
	)

set(SOURCES ${SOURCES}
	PARENT_SCOPE
	)

set(HEADERS ${HEADERS}
	PARENT_SCOPE
	)
