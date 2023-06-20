#!/bin/bash

BASE_DIR=/home/vldb/mysql-5.7.33
BUILD_DIR=/usr/local/mysql
PASSWD=vldb#7988

# Make a directory for build
if [ ! -d "$BUILD_DIR" ]; then
    echo "Make a directory for build"
    mkdir bld
fi

cd $BUILD_DIR

rm -rf CMakeCache.txt
echo $PASSWD | sudo -S rm -rf CMakeFiles/*

# Build and install the source code
if [ "$1" = "--origin" ]; then
  # No caching
  BUILD_FLAGS=""
elif [ "$1" = "--tpcc" ]; then
  # Enable Flash-Friendly Checkpoint
  BUILD_FLAGS="-DUNIV_TPCC_MONITOR"
elif [ "$1" = "--warm" ]; then
  BUILD_FLAGS="-DUNIV_WARM_BUF_CACHE -DUNIV_TPCC_MONITOR"
else
  BUILD_FLAGS=""
fi

echo "Start build using $BUILD_FLAGS"

cd $BASE_DIR

cmake -DWITH_DEBUG=0 -DCMAKE_C_FLAGS="$BUILD_FLAGS" -DCMAKE_CXX_FLAGS="$BUILD_FLAGS" \
-DDOWNLOAD_BOOST=ON -DWITH_BOOST=$BASE_DIR -DENABLED_LOCAL_INFILE=1 \
-DCMAKE_INSTALL_PREFIX=$BUILD_DIR

make -j16
echo $PASSWD | sudo -S make install

#cp ../START.sh ${BUILD_DIR}/bin/

