#!/bin/sh
# Usage: ./install_cmake.sh <cmake_version>
# <cmake_version> is a semver of the form X.Y.Z[pre-release version]
set -ev

cmake_version=$1
cmake_installer=cmake-${cmake_version}-Linux-x86_64.sh

cd /tmp
wget https://github.com/Kitware/CMake/releases/download/v${cmake_version}/${cmake_installer}
sh ${cmake_installer} --prefix=. --exclude-subdir
