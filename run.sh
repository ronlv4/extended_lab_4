#!/bin/bash -xe

git pull
make clean
make $1
./bin/$1
