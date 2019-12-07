#!/bin/bash

BUILD_TYPE="Release"

if [ -z $1 ]; then

    echo -e "No build mode given!"
    exit

fi

if [ $1 == "debug" ]; then
    echo -e "Build type: Debug"
    BUILD_TYPE="Debug"
elif [ $1 == "release" ]; then
    echo -e "Build type: Release"
else
    echo -e "Invalid build type!"
    exit
fi

if [ -d "$(pwd)/build" ]; then

    rm -r $(pwd)/build

fi

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_C_COMPILER=$(which clang) -DCMAKE_CXX_COMPILER=$(which clang++)
