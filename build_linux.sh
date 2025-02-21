#!/bin/bash

sudo chmod -R 777

mkdir build
cd build
cmake ..
make -j4

