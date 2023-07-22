#!/usr/bin/env bash

echo "==================== Checking build directory..."
cd "$(dirname $0)"
mkdir -p build
cd build

echo "==================== Running CMake..."
echo "With custom flags $1"
CUSTOM_FLAGS="$1"
export CUSTOM_FLAGS
cmake -DCMAKE_BUILD_TYPE=Release ..
if [ $? -ne 0 ]; then
	exit 1
fi

echo "==================== Running Make..."
make
if [ $? -ne 0 ]; then
	exit 1
fi