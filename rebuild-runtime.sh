#! /usr/bin/bash
cmake -S . -B . -DCXX_RUNTIME=ON
cmake --build . -j$(nproc) 2>build.log --clean-first
./qc ./runtime.qc -co -nrt -O3 -o runtime.ll
cmake -S . -B . -DCXX_RUNTIME=OFF
cmake --build . -j$(nproc) 2>build.log --clean-first
