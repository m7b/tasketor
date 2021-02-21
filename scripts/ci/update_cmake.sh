#!/bin/bash

#https://github.com/travis-ci/travis-build.git/lib/travis/build/script/templates/header.sh
travis_retry() {
  local result=0
  local count=1
  while [ $count -le 3 ]; do
    [ $result -ne 0 ] && {
      echo -e "\n${ANSI_RED}The command \"$@\" failed. Retrying, $count of 3.${ANSI_RESET}\n" >&2
    }
    "$@"
    result=$?
    [ $result -eq 0 ] && break
    count=$(($count + 1))
    sleep 1
  done

  [ $count -gt 3 ] && {
    echo -e "\n${ANSI_RED}The command \"$@\" failed 3 times.${ANSI_RESET}\n" >&2
  }

  return $result
}


# first we create a directory for the CMake binaries
DEPS_DIR="${TRAVIS_BUILD_DIR}/deps"
mkdir ${DEPS_DIR} && cd ${DEPS_DIR}
# we use wget to fetch the cmake binaries
travis_retry wget --no-check-certificate https://cmake.org/files/v3.20/cmake-3.20.0-rc1-linux-x86_64.tar.gz
# this is optional, but useful:
# do a quick md5 check to ensure that the archive we downloaded did not get compromised
echo "455ff919e07f3afb938abd3c0ee7f234b690699f4980065f6001407995b0e6b4 *cmake-3.20.0-rc1-linux-x86_64.tar.gz" > cmake_sha256.txt
sha256sum -c cmake_sha256.txt
# extract the binaries; the output here is quite lengthy,
# so we swallow it to not clutter up the travis console
tar -xvf cmake-3.20.0-rc1-linux-x86_64.tar.gz > /dev/null
mv cmake-3.20.0-rc1-linux-x86_64 cmake-install
# add both the top-level directory and the bin directory from the archive
# to the system PATH. By adding it to the front of the path we hide the
# preinstalled CMake with our own.
PATH=${DEPS_DIR}/cmake-install:${DEPS_DIR}/cmake-install/bin:$PATH
# don't forget to switch back to the main build directory once you are done
cd ${TRAVIS_BUILD_DIR}
