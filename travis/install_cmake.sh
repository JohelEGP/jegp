#!/bin/sh
set -ev

cmake_version=3.12
cmake_patch=0
cmake_pre=-rc1
cmake_installer=cmake-${cmake_version}.${cmake_patch}${cmake_pre}-Linux-x86_64.sh

cd /tmp
wget https://cmake.org/files/v${cmake_version}/${cmake_installer}
sh ${cmake_installer} --prefix=. --exclude-subdir
