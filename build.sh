#!/bin/bash
mkdir -p build
cd build
g++ ../list/removesublist.cpp -o remove
g++ ../rename/rename.cpp -o rename