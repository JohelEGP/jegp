#!/bin/sh
# Usage: ./install_clang.sh <clang_version>
# <clang_version> is a semver of the form X.Y.Z
set -ev

clang_version=$1
clang_archive=clang+llvm-${clang_version}-x86_64-linux-gnu-ubuntu-14.04.tar.xz

cd /tmp
wget http://releases.llvm.org/${clang_version}/${clang_archive}
tar xf ${clang_archive} --strip-components=1
