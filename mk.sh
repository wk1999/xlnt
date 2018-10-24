#!/bin/sh

APP_FOLDER="wei"
WORK_HOST="eselnts1329"

if [[ $1 = "-c" ]]; then
    echo "make clean"
    git clean -xfd
    exit 0
fi

if [[ $1 = "-s" ]]; then
    echo "make static"
    static="-DSTATIC=on"
fi

if [[ `uname -n` = ${WORK_HOST} ]]; then
    echo "work env compilation"
    export CC=/app/vbuild/RHEL6-x86_64/gcc/7.3.0/bin/gcc
    export CXX=/app/vbuild/RHEL6-x86_64/gcc/7.3.0/bin/g++
fi

echo "make lib"
cmake ${static} .
make

if [ ${APP_FOLDER} ]; then
    echo "make APP"
    make -C ${APP_FOLDER}
fi
