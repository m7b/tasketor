#An Engineer’s Guide to Unit Testing – CMake And Boost Unit Tests
#http://neyasystems.com/an-engineers-guide-to-unit-testing-cmake-and-boost-unit-tests/

#Setup CMake to run tests
ENABLE_TESTING()

FIND_PACKAGE(Boost REQUIRED locale unit_test_framework)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#I like to keep test files in a separate source directory called test
FILE(GLOB TEST_SRCS *.cpp)

#Run through each source
FOREACH(testSrc ${TEST_SRCS})
        #Extract the filename without an extension (NAME_WE)
        get_filename_component(testName ${testSrc} NAME_WE)

        #Add compile target
        add_executable(${testName} ${testSrc})

        #link to Boost libraries AND your targets and dependencies
        target_link_libraries(
            ${testName}
			this_project
            ${CONAN_LIBS}
		#	${SQLite3_LIBRARIES}
            ${Boost_LIBRARIES}
            ws2_32
            -static
        )

        #Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${testName}
                 COMMAND ${testName} --report_level=detailed)
ENDFOREACH(testSrc)