#!/bin/sh
# Usage: ./meet_doc_prereq.sh
set -ev

cd /tmp

npm install mathjax-node-cli split

stack_archive=linux-x86_64-static.tar.gz
wget https://get.haskellstack.org/stable/${stack_archive}
tar xf ${stack_archive} --strip-components=1
mv stack bin
