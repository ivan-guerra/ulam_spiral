#!/bin/bash

source config.sh

Help()
{
    echo "build ulam spiral visualizer"
    echo "usage: build.sh [OPTION]..."
    echo "options:"
    echo -e "\t-g    enable debug info"
    echo -e "\t-t    build unit tests"
    echo -e "\t-d    build doxygen docs"
    echo -e "\t-h    print this help message"
}

Main()
{
    # Create the build directory if it does not already exist.
    mkdir -pv "$US_BUILD_DIR"

    # Set the build type according to the first program arg if any. Default is
    # release.
    BUILD_TYPE="RELEASE"
    BUILD_DOCS="OFF"
    BUILD_TESTS="OFF"
    while getopts ":hgtd" flag
    do
        case "$flag" in
            g) BUILD_TYPE="DEBUG" ;;
            t) BUILD_TESTS="ON" ;;
            d) BUILD_DOCS="ON" ;;
            h) Help
                exit 0 ;;
            \?) echo "error: invalid option '$OPTARG'"
                exit 1 ;;
        esac
    done

    pushd "$US_BUILD_DIR" > /dev/null || exit 1
    cmake ../ \
        -DBUILD_DOCS="$BUILD_DOCS" \
        -DBUILD_TESTS="$BUILD_TESTS" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
        -DCMAKE_INSTALL_PREFIX="$US_BIN_DIR" \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" && \
        make -j"$(nproc)" all && \
        make install
    popd > /dev/null || exit 1
}

Main "$@"
