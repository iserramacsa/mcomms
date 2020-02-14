## Gtest configuration

option(ENABLE_TESTS "Enable tests" OFF)

if (WIN32)
	##TODO
		set(ENABLE_TESTS ON)
elseif(UNIX)
	if (CMAKE_CXX_COMPILER MATCHES "gnueabihf")
		message("Linux arm-gnueabihf")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-linux-gnueabihf)
	elseif(CMAKE_CXX_COMPILER MATCHES "gnueabi")
		message("Linux arm-linux-gnueabi")
		set(LIB_PREFIX		$ENV{HOME}/TIJLibraries/arm-fs-linux-gnueabi)
	else()
		set(ENABLE_TESTS ON)
	endif()
endif()

# GTest integration
if (${ENABLE_TESTS})
	set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
	    				GTest::GTest
						GTest::Main
						gmock
						gmock_main
						)
    enable_testing()
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})
	include_directories(${GMOCK_INCLUDE_DIRS})
	add_definitions(-DVIRTUAL_MOCK=virtual)
else()
	add_definitions(-DVIRTUAL_MOCK=)	
endif()
