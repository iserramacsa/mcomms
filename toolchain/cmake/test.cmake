## Gtest configuration

option(ENABLE_TESTS "Enable tests" OFF)

if (WIN32)
        message("Windows compilation")
        set (GTEST_ROOT "C:/Program Files (x86)/googletest-distribution")
        ##TODO
elseif(UNIX)
        if (CMAKE_CXX_COMPILER MATCHES "gnueabihf")
                message("Linux arm-gnueabihf")
        elseif(CMAKE_CXX_COMPILER MATCHES "gnueabi")
                message("Linux arm-linux-gnueabi")
        else()
                message("Linux compilation")
        endif()
endif()

# GTest integration
if (${ENABLE_TESTS})
    message("Enabling test for " ${PROJECT_NAME})
    if (WIN32)
        set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
                                GTest::GTest
                                GTest::Main
                                ${GTEST_ROOT}/lib/gmock.lib
                                ${GTEST_ROOT}/lib/gmock_main.lib
                                )
    else()
        set(EXTERNAL_LIBS	${EXTERNAL_LIBS}
                                GTest::GTest
                                GTest::Main
                                gmock
                                gmock_main
                                )
    endif()
    enable_testing()
    find_package(GTest REQUIRED)
    if (NOT GMOCK_INCLUDE_DIRS)
        set(GMOCK_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS})
    endif()

    include_directories(${GTEST_INCLUDE_DIRS})
    include_directories(${GMOCK_INCLUDE_DIRS})
    message("GTEST_INCLUDE_DIRS:  ${GTEST_INCLUDE_DIRS}")
    message("GMOCK_INCLUDE_DIRS:  ${GMOCK_INCLUDE_DIRS}")
    add_definitions(-DVIRTUAL_MOCK=virtual)
else()
    add_definitions(-DVIRTUAL_MOCK=)
endif()
