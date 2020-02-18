##############################
## Tools library options	##
##############################

option(USE_SIGNALS "Add SimpleSignal code" OFF)


if (${USE_SIGNALS})
	add_definitions(-DSSIGNALS=true)
endif()
