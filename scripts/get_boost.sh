#!/bin/bash

#wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
#tar --bzip2 -xf boost_1_75_0.tar.bz2

cd boost_1_75_0
./bootstrap.sh gcc --prefix=/usr/local
./b2 install toolset=gcc address-model=64 --with-filesystem --with-date_time --with-test --with-locale
cd ..
