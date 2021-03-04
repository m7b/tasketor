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



include(FetchContent)
SET(FETCHCONTENT_QUIET OFF)
SET(GIT_SHALLOW ON)
SET(GIT_PROGRESS ON)

message("BOOST NOT POPULATED *********************************************************")

if(WIN32)
	# for Windows operating system in general
	message("BOOST set booststrap command for WINDOWS ********************")
#	set(boost_bootstrap_cmd "${CMAKE_CURRENT_SOURCE_DIR}/patches/test.bat gcc")
	set(boost_bootstrap_cmd "cmd /c \"ECHO Hallo Welt !!!\"")
	set(boost_b2_cmd        b2.exe)
endif()

if(UNIX AND NOT APPLE)
	# for Linux, BSD, Solaris, Minix
	message("BOOST set booststrap command for LINUX **********************")
	set(boost_bootstrap_cmd ./bootstrap.sh)
	set(boost_b2_cmd        ./b2)
endif()

message("Bootstrap command is ${boost_bootstrap_cmd}")
message("b2 command is ${boost_b2_cmd}")



if(NOT EXISTS "${boostorg_SOURCE_DIR}/${boost_b2_cmd}")
	message("b2 command not exist. Try to compile it ****")
	message("Running ${boost_bootstrap_cmd} in directory ${boostorg_SOURCE_DIR}")
	Execute_Process(
		COMMAND ${boost_bootstrap_cmd}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/patches
	)
endif()


message("BOOST POPULATED *********************************************************")









# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${CMAKE_CURRENT_BINARY_DIR}"
                    "${PROJECT_SOURCE_DIR}/include"
#                    "${Boost_INCLUDE_DIRS}"
                    "${boostorg_SOURCE_DIR}"
                    "${sqlite3_SOURCE_DIR}"
                    "${spdlog_SOURCE_DIR}/include"
)



add_library(
    this_project
    src/C_DbHandle.cpp
    src/C_Project.cpp
	${sqlite3_SOURCE_DIR}/sqlite3.c
)



# add the executable
add_executable(
    ${CMAKE_PROJECT_NAME}
#    WIN32
    src/main.cpp
#    res/resource.rc
#    res/svn.rc
)



# target compile options
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-g>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Debug>:-O0>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC $<$<CONFIG:Release>:-Ofast>)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -funroll-loops)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -std=gnu++11)
#target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -mthreads)
#target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -pthread)
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





# # generate CHANGELOG from *.md to *.html (on change)
# FIND_PROGRAM(PANDOC_EXECUTABLE V:/pandoc-2.6-windows-x86_64/pandoc.exe)
# SET(CHANGELOG_MD   ${PROJECT_SOURCE_DIR}/CHANGELOG.md)
# SET(CHANGELOG_HTML ${CMAKE_CURRENT_BINARY_DIR}/CHANGELOG.html)
# ADD_CUSTOM_COMMAND(
#     OUTPUT ${CHANGELOG_HTML}
#     COMMAND ${PANDOC_EXECUTABLE} ${CHANGELOG_MD} -o ${CHANGELOG_HTML}
#     DEPENDS ${CHANGELOG_MD}
# )
# ADD_CUSTOM_TARGET(
#     changelog
#     DEPENDS ${CHANGELOG_HTML}
#     COMMENT "Create changelog file (md to html)"
# )
# SET_PROPERTY(SOURCE res/resource.rc APPEND PROPERTY OBJECT_DEPENDS ${CHANGELOG_HTML})


# # generate TOOLCHAIN from *.md to *.html (on change)
# SET(TOOLCHAIN_MD   ${PROJECT_SOURCE_DIR}/TOOLCHAIN.md)
# SET(TOOLCHAIN_HTML ${CMAKE_CURRENT_BINARY_DIR}/TOOLCHAIN.html)
# ADD_CUSTOM_COMMAND(
#     OUTPUT ${TOOLCHAIN_HTML}
#     COMMAND ${PANDOC_EXECUTABLE} ${TOOLCHAIN_MD} -o ${TOOLCHAIN_HTML}
#     DEPENDS ${TOOLCHAIN_MD}
# )
# ADD_CUSTOM_TARGET(
#     toolchain
#     DEPENDS ${TOOLCHAIN_HTML}
#     COMMENT "Create toolchain file (md to html)"
# )
# SET_PROPERTY(SOURCE res/resource.rc APPEND PROPERTY OBJECT_DEPENDS ${TOOLCHAIN_HTML})






# if(CMAKE_BUILD_TYPE STREQUAL Release)
#     MESSAGE(STATUS "Do minimal size release stuff")
#     FIND_PROGRAM(UPX_EXECUTABLE V:/upx-3.96-win64/upx.exe)
#     ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
#     COMMAND ${UPX_EXECUTABLE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
#     COMMENT "Running UPX packer ..."
#     )
# endif()


#message("tasketor_BINARY_DIR is ${OpenChemistry_BINARY_DIR}")
#message("OpenChemistry_DEFAULT_ARGS is ${OpenChemistry_DEFAULT_ARGS}")
#message("OpenChemistry_THIRDPARTYLIBS_ARGS is ${OpenChemistry_THIRDPARTYLIBS_ARGS}")
#message("OpenChemistry_INSTALL_PREFIX is ${OpenChemistry_INSTALL_PREFIX}")
#message("sqlite3_SOURCE_DIR is ${sqlite3_SOURCE_DIR}")
#message("spdlog_SOURCE_DIR is ${spdlog_SOURCE_DIR}")
#message("boostorg_SOURCE_DIR is ${boostorg_SOURCE_DIR}")



if(WIN32)
# for Windows operating system in general


	# link libraries
	target_link_libraries(
		${CMAKE_PROJECT_NAME}
		this_project
		${Boost_LIBRARIES}
		${SQLite3_LIBRARIES}
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
		${SQLite3_LIBRARIES}
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






#ADD_SUBDIRECTORY(test)
