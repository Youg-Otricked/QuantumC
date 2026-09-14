#!/usr/bin/env bash
set -e

RUNS=500

bench_cmd() {
    local label="$1"
    shift
    local cmd=("$@")
    echo "-$label ($RUNS runs)..."
    "${cmd[@]}" > /dev/null 2>&1
    for ((i = 1; i <= RUNS; i++)); do
        /usr/bin/time -f "%e %U %S %P %M %R %F %I %O" "${cmd[@]}" 2>&1 > /dev/null
    done | tr -d '%' | awk '
      {
        elapsed += $1;
        user    += $2;
        sys     += $3;
        cpu     += $4;
        rss     += $5;
        min_pf  += $6;
        maj_pf  += $7;
        fs_in   += $8;
        fs_out  += $9;
      }
      END {
        n = NR;
        printf "  Time:     %8.2f ms (User: %.2f ms, Sys: %.2f ms, CPU: %.1f%%)\n", (elapsed/n)*1000, (user/n)*1000, (sys/n)*1000, cpu/n;
        printf "  Memory:   %8.2f KB (%.2f MB peak RSS)\n", rss/n, (rss/n)/1024.0;
        printf "  Faults:   %8.1f minor, %d major\n", min_pf/n, maj_pf/n;
        printf "  I/O:      %8.1f in, %8.1f out\n\n", fs_in/n, fs_out/n;
      }'
}
echo "Clang vs C^4"
for opt in O0 O1 O2 O3; do
    echo "[ -$opt]"
    bench_cmd "C++ Compile (-$opt)" clang++ -$opt bench.cpp -o bench_cpp_$opt
    bench_cmd "C^4 Compile (-$opt)" ./qc -$opt bench.qc -o bench_qc_$opt
    bench_cmd "C++ Run     (-$opt)" ./bench_cpp_$opt
    bench_cmd "C^4 Run     (-$opt)" ./bench_qc_$opt
done
