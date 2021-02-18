#!/bin/bash

wget https://www.sqlite.org/2020/sqlite-autoconf-3340000.tar.gz
tar xvfz sqlite-autoconf-3340000.tar.gz

cd sqlite-autoconf-3340000
./configure --prefix=/usr/local
make
make install
cd ..
