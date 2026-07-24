#! /usr/bin/bash
cmake -S . -B . -DCXX_RUNTIME=OFF
cmake --build . -j$(nproc) 2>build.log --clean-first
