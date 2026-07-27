#!/usr/bin/env bash
set -euo pipefail
jobs="$(getconf _NPROCESSORS_ONLN 2>/dev/null || sysctl -n hw.ncpu)" 
cmake -S . -B . -DCXX_RUNTIME=ON
cmake --build . --parallel "$jobs" 2>build.log --clean-first
./qc ./runtime.qc -co -nrt -O3 -o runtime.ll
cmake -S . -B . -DCXX_RUNTIME=OFF
cmake --build . --parallel "$jobs" 2>build.log --clean-first
