#!/bin/bash

# Root directory.
US_PROJECT_PATH="$(dirname "$(pwd)")"

# Docs directory.
export US_DOCS_DIR="${US_PROJECT_PATH}/docs/html"

# CMake build files and cache.
export US_BUILD_DIR="${US_PROJECT_PATH}/build"

# Binary directory.
export US_BIN_DIR="${US_PROJECT_PATH}/bin"
