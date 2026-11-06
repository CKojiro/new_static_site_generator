#!/bin/bash

set -e

cmake -S . -B build
cmake --build build

./main "/new_static_site_generator/"