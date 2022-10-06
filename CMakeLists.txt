cmake_minimum_required(VERSION 3.14...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(tasketor VERSION 0.0.0
                 DESCRIPTION "Helping assigning periodicaly tasks"
                 LANGUAGES C CXX)


set(PROJECT_VERSION_DEV_STAGE "\" (Pre-alpha)\"")
#SET(PROJECT_VERSION_DEV_STAGE "\" (Alpha)\"")
#SET(PROJECT_VERSION_DEV_STAGE "\" (Beta)\"")
#SET(PROJECT_VERSION_DEV_STAGE "")



configure_file(
    ${PROJECT_SOURCE_DIR}/include/version.h.in
    ${PROJECT_BINARY_DIR}/version.h
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")



if(WIN32)
    # for Windows operating system in general
	include("cmake/OSWindows.cmake")
endif()

if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
	include("cmake/OSLinux.cmake")
endif()


# ADD_SUBDIRECTORY(doc)

## Conan Package Manager
## for ...
##   - sqlite
##   - spdlog
## SET(CONAN_DISABLE_CHECK_COMPILER ON CACHE BOOL "Disabling compiler check (Conan)")  <-- this does not work at this stage
## Make dependencies available
INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()





## Cmake FetchContent
## for ...
##   - Boost
INCLUDE(FetchContent)
SET(FETCHCONTENT_QUIET OFF)
message("++ Fetch Content Mode is set to ${CMAKE_FETCHCONTENT_MODE}")
if(CMAKE_FETCHCONTENT_MODE STREQUAL OFF)
    SET(FETCHCONTENT_FULLY_DISCONNECTED ON)
endif()
SET(GIT_SHALLOW ON)
SET(GIT_PROGRESS ON)
#   - Boost
SET(GIT_REPOSITORY_BOOST     https://github.com/boostorg/boost.git)
SET(GIT_TAG_BOOST            boost-1.80.0)
INCLUDE(fetch_boost)



# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}/include"
					"${CONAN_INCLUDE_DIRS}"
                    "${Boost_INCLUDE_DIRS}"
)



add_library(
    this_project
    src/C_DbHandle.cpp
    src/C_Project.cpp
#    ${CONAN_LIBS}
)



# add the executable
add_executable(
    ${CMAKE_PROJECT_NAME}
    src/main.cpp
)



# target compile options
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-g>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-O0>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:-Ofast>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -funroll-loops)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -pipe)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall)


# target compile definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DEXE_NAME=${CMAKE_PROJECT_NAME})
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D__GNUWIN32__)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D__WXMSW__)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -D_WIN32_WINNT=0x0601)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DwxUSE_UNICODE)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:wxDEBUG_LEVEL=0>)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:wxDEBUG_LEVEL=1>)




if(WIN32)
# for Windows operating system in general

	# link libraries
	target_link_libraries(
		${CMAKE_PROJECT_NAME}
		this_project
		${Boost_LIBRARIES}
        ${CONAN_LIBS}
		##    shlwapi
		##    version
		##    oleacc
		-static
		-static-libgcc
		-static-libstdc++
		$<$<CONFIG:Release>:-s>
	)
endif()

if(UNIX AND NOT APPLE)
# for Linux operating system in general

	# link libraries
	target_link_libraries(
		${CMAKE_PROJECT_NAME}
		this_project
		${Boost_LIBRARIES}
        ${CONAN_LIBS}
		##    shlwapi
		##    version
		##    oleacc
#		-licuuc
#		-licui18n
		-ldl       #linux
		-lpthread  #linux
		-static
		-static-libgcc
		-static-libstdc++
		$<$<CONFIG:Release>:-s>
	)


endif()

add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/docs/Timetable.xlsx
                ${CMAKE_CURRENT_BINARY_DIR}/bin/Timetable.xlsx)


ADD_SUBDIRECTORY(tests)
