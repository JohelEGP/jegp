#!/bin/sh
set -ev

cmake_version=3.14
cmake_patch=5
cmake_pre=
cmake_installer=cmake-${cmake_version}.${cmake_patch}${cmake_pre}-Linux-x86_64.sh

cd /tmp
wget https://cmake.org/files/v${cmake_version}/${cmake_installer}
sh ${cmake_installer} --prefix=. --exclude-subdir
