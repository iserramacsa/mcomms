##############################
## Tools library options	##
##############################

option(USE_SIGNALS "Add SimpleSignal code" OFF)


if (${USE_SIGNALS})
	add_definitions(-DSSIGNALS=1)
endif()
