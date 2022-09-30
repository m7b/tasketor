@ECHO OFF
SET PROJECT_NAME=tasketor
REM Clear output
REM CLS

REM Extend search path for this batch file
REM https://stackoverflow.com/questions/141344/how-to-check-if-directory-exists-in-path
SET pathVar=V:\cmake-3.24.0-rc4-windows-x86_64\bin
CALL scripts\addPath pathVar /B
SET pathVar=V:\nsis-3.05\bin
CALL scripts\addPath pathVar /B
SET pathVar=V:\doxygen-1.8.15.windows.x64.bin
CALL scripts\addPath pathVar /B
SET pathVar=V:\graphviz-2.38\release\bin
CALL scripts\addPath pathVar /B
SET pathVar=Z:\bin
CALL scripts\addPath pathVar /B

REM Set Defaults
SET fetchcontent=OFF
SET buildtype=Release
SET pack=OFF
SET generator=MinGW Makefiles
SET j_option=7
SET verbose=OFF

REM Handle parameters
:Loop
REM Show help and exit
IF     [%1]==[-h]           GOTO HELP
IF     [%1]==[--help]       GOTO HELP
IF     [%1]==[-fc]            GOTO FETCHCONTENT
IF     [%1]==[--fetchcontent] GOTO FETCHCONTENT
IF     [%1]==[-r]           GOTO BUILDRELEASE
IF     [%1]==[--release]    GOTO BUILDRELEASE
IF     [%1]==[-p]           GOTO PACKAGE
IF     [%1]==[--package]    GOTO PACKAGE
IF     [%1]==[-d]           GOTO BUILDDEBUG
IF     [%1]==[--debug]      GOTO BUILDDEBUG
IF     [%1]==[-j]           GOTO JOBS
IF     [%1]==[--jobs]       GOTO JOBS
IF     [%1]==[-v]           GOTO VERBOSE
IF     [%1]==[--verbose]    GOTO VERBOSE
IF     [%1]==[-cb]          GOTO BUILDCODEBLOCKS
IF     [%1]==[--codeblocks] GOTO BUILDCODEBLOCKS
IF     [%1]==[-doc]         GOTO DOC
IF     [%1]==[--document]   GOTO DOC
IF     [%1]==[-c]           GOTO CLEAN
IF     [%1]==[--clean]      GOTO CLEAN
IF     [%1]==[-hc]          GOTO HARDCLEAN
IF     [%1]==[--hardclean]  GOTO HARDCLEAN
IF NOT [%1]==[]             GOTO HELP
GOTO BUILD

:HELP
ECHO Perform a build or a clean.
ECHO:
ECHO %~nx0 ^<options^>
ECHO:
ECHO Available options:
ECHO:
ECHO   -h,   --help          Show this help message.
ECHO   -fc,  --fetchcontent  Fetch and populate additional content/libraries.
ECHO                         This should be done for first time build or after cleanup.
ECHO   -r,   --release       Build a release application in build directory.
ECHO   -d,   --debug         Build a debug application in build directory.
ECHO   -j ^<n^>, --jobs ^<n^>    Number of executing parallel jobs.
ECHO   -v,   --verbose       Switches verbose mode on.
ECHO   -p,   --package       Build an installer package.
ECHO   -cb,  --codeblocks    Creates a code blocks project file.
ECHO   -doc, --document      Creates doxygen document
ECHO   -c,   --clean         Performs a cmake clean (target clean).
ECHO   -hc,  --hardclean     Deletes the complete build directory.
ECHO:
ECHO:
ECHO Example usage:
ECHO:
ECHO %~nx0 -d -cb (create a debug codeblocks project and build)
ECHO:
GOTO EXIT

:FETCHCONTENT
SET fetchcontent=ON
SHIFT
GOTO Loop

:BUILDRELEASE
SET buildtype=Release
SHIFT
GOTO Loop

:PACKAGE
SET pack=ON
SHIFT
GOTO Loop

:BUILDDEBUG
SET buildtype=Debug
SHIFT
GOTO Loop

:JOBS
SET j_option=%2
SHIFT
SHIFT
GOTO Loop

:VERBOSE
SET verbose=ON
SHIFT
GOTO Loop

:BUILDCODEBLOCKS
SET generator=CodeBlocks - MinGW Makefiles
SHIFT
GOTO Loop

:BUILD
SET "startTime=%time: =0%"
IF NOT EXIST build\NUL MKDIR build
CD build
cmake -G "%generator%" -DCMAKE_VERBOSE_MAKEFILE:BOOL=%verbose% -DCMAKE_BUILD_TYPE=%buildtype% -DCMAKE_FETCHCONTENT_MODE=%fetchcontent% ..
REM cmake -G "%generator%" -DCMAKE_SH="CMAKE_SH-NOTFOUND" -DCMAKE_VERBOSE_MAKEFILE:BOOL=%verbose% -DCMAKE_BUILD_TYPE=%buildtype% ..
IF "%pack%" == "OFF" (
    cmake --build . -- -j %j_option%
) ELSE (
    cmake --build . -- package -j %j_option%
)

SET "endTime=%time: =0%"
IF %ERRORLEVEL% GEQ 1 GOTO ERROR
CD ..
GOTO DONE

:INSTALL
CD build
REM IF EXIST check.exe cmake -E copy check.exe ..
CD ..
GOTO EXIT

:DOC
SET "startTime=%time: =0%"
IF NOT EXIST build\NUL MKDIR build
CD build
cmake -G "%generator%"-DCMAKE_BUILD_TYPE=%buildtype% ..
cmake --build . -- doxygen
SET "endTime=%time: =0%"
IF %ERRORLEVEL% GEQ 1 GOTO ERROR
CD ..
GOTO DONE

:CLEAN
IF EXIST build\NUL cmake --build build --target clean
GOTO EXIT

:HARDCLEAN
IF NOT EXIST build\NUL GOTO EXIT
IF EXIST build\build_statistics.txt MOVE build\build_statistics.txt %temp%
RD /S /Q build
MKDIR build
IF EXIST build\build_statistics.txt MOVE %temp%\build_statistics.txt build
GOTO EXIT

:J_OPTION
SET SET j_option=%2
SHIFT
SHIFT
GOTO Loop

:ERROR
ECHO:
ECHO *** ERROR
ECHO Errorcode is %ERRORLEVEL%
PAUSE
GOTO EXIT

:DONE
ECHO:

REM Settings for duration calculation
SETLOCAL EnableDelayedExpansion

REM Get elapsed time:
SET "end=!endTime:%time:~8,1%=%%100)*100+1!"  &  SET "start=!startTime:%time:~8,1%=%%100)*100+1!"
SET /A "elap=((((10!end:%time:~2,1%=%%100)*60+1!%%100)-((((10!start:%time:~2,1%=%%100)*60+1!%%100), elap-=(elap>>31)*24*60*60*100"

REM Convert elapsed time to HH:MM:SS:CC format:
SET /A "cc=elap%%100+100,elap/=100,ss=elap%%60+100,elap/=60,mm=elap%%60+100,hh=elap/60+100"

REM Print statistics
SET stat_file=build\build_statistics.txt
SET out_file=build\%PROJECT_NAME%.exe
ECHO ----------------------- >> %stat_file%
ECHO Date:       %date% >> %stat_file%
ECHO Build Type: %buildtype% >> %stat_file%
ECHO j Option:   %j_option% >> %stat_file%
ECHO Pack:       %pack% >> %stat_file%
ECHO Verbose:    %verbose% >> %stat_file%
ECHO Start:      %startTime% >> %stat_file%
ECHO End:        %endTime% >> %stat_file%
ECHO Elapsed:    %hh:~1%%time:~2,1%%mm:~1%%time:~2,1%%ss:~1%%time:~8,1%%cc:~1% >> %stat_file%
FOR %%I IN (%out_file%) DO ECHO Size:       %%~zI Bytes >> %stat_file%

:EXIT
ECHO beendet