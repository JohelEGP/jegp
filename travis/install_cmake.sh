#!/bin/sh
set -ev

cmake_version=3.11
cmake_patch=3
cmake_installer=cmake-${cmake_version}.${cmake_patch}-Linux-x86_64.sh

cd /tmp
wget https://cmake.org/files/v${cmake_version}/${cmake_installer}
sh ${cmake_installer} --prefix=. --exclude-subdir
