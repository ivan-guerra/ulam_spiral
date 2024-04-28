#!/bin/bash

source config.sh

# Remove the docs directory.
if [ -d "$US_DOCS_DIR" ]
then
    echo "removing '$US_DOCS_DIR'"
    rm -rf "$US_DOCS_DIR"
fi

# Remove the CMake build directory.
if [ -d "$US_BUILD_DIR" ]
then
    echo "removing '$US_BUILD_DIR'"
    rm -rf "$US_BUILD_DIR"
fi

# Remove the binary directory.
if [ -d "$US_BIN_DIR" ]
then
    echo "removing '$US_BIN_DIR'"
    rm -rf "$US_BIN_DIR"
fi
