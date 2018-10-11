#!/bin/sh

export CC=/app/vbuild/RHEL6-x86_64/gcc/7.3.0/bin/gcc
export CXX=/app/vbuild/RHEL6-x86_64/gcc/7.3.0/bin/g++

#cmake . -DCMAKE_INSTALL_RPATH="/app/vbuild/RHEL6-x86_64/gcc/7.3.0/lib64/"
#cmake . -DCMAKE_SKIP_RPATH=TRUE -DCMAKE_SKIP_BUILD_RPATH=TRUE -DCMAKE_SKIP_INSTALL_RPATH=TRUE -DCMAKE_INSTALL_RPATH=/app/vbuild/RHEL6-x86_64/gcc/7.3.0/lib64/
cmake .
make
