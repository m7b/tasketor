FetchContent_Declare(
    boostorg
    GIT_REPOSITORY ${GIT_REPOSITORY_BOOST}
    GIT_TAG        ${GIT_TAG_BOOST}
    )

#FetchContent_MakeAvailable(boostorg)
FetchContent_GetProperties(boostorg)

if(NOT boostorg_POPULATED)
    message("BOOST NOT POPULATED *********************************************************")
    FetchContent_Populate(boostorg)
    
    if(WIN32)
        # for Windows operating system in general
        message("BOOST set booststrap command for WINDOWS ********************")
        set(boost_bootstrap_cmd  "cmd")
        set(boost_bootstrap_arg1 "/c")
        set(boost_bootstrap_arg2 "bootstrap.bat gcc")
        set(boost_b2_cmd         b2.exe)
    endif()

    if(UNIX AND NOT APPLE)
        # for Linux, BSD, Solaris, Minix
        message("BOOST set booststrap command for LINUX **********************")
        set(boost_bootstrap_cmd  "sh")
        set(boost_bootstrap_arg1 "-c")
        set(boost_bootstrap_arg2 "./bootstrap.sh")
        set(boost_b2_cmd         ./b2)
    endif()


    
    message("Bootstrap command is ${boost_bootstrap_cmd}")
    message("b2 command is ${boost_b2_cmd}")
    
	file(
        COPY        ${CMAKE_CURRENT_SOURCE_DIR}/patches/boost/bootstrap.bat
        DESTINATION ${boostorg_SOURCE_DIR}
    )
	
    if(NOT EXISTS "${boostorg_SOURCE_DIR}/${boost_b2_cmd}")
        message("b2 command not exist. Try to compile it ****")
        message("Running ${boost_bootstrap_cmd} in directory ${boostorg_SOURCE_DIR}")
        Execute_Process(
            COMMAND ${boost_bootstrap_cmd} ${boost_bootstrap_arg1} ${boost_bootstrap_arg2}
            WORKING_DIRECTORY ${boostorg_SOURCE_DIR}
        )
    endif()

    Execute_Process(
        COMMAND ${boost_b2_cmd} headers
        WORKING_DIRECTORY ${boostorg_SOURCE_DIR}
    )
    Execute_Process(
        COMMAND ${boost_b2_cmd} toolset=gcc address-model=64 --with-filesystem --with-date_time --with-locale --with-test
        WORKING_DIRECTORY ${boostorg_SOURCE_DIR}
    )
    message("BOOST POPULATED *********************************************************")
	
#    set(Boost_DEBUG ON)
    ##SET(Boost_DEBUG ON)
    ##SET(Boost_COMPILER "-mgw92")
    set(Boost_NO_WARN_NEW_VERSIONS     ON)
    set(Boost_ARCHITECTURE         "-x64")
    set(Boost_USE_STATIC_LIBS          ON)
    set(Boost_USE_MULTITHREADED        ON)
    set(Boost_USE_STATIC_RUNTIME      OFF)
    set(BOOST_ROOT ${boostorg_SOURCE_DIR})
    FIND_PACKAGE(Boost REQUIRED filesystem date_time locale)
#    FIND_PACKAGE(Boost 1.76.0 REQUIRED filesystem date_time)
    #unit_test_framework
	
endif()
