#!/usr/bin/env bash
set -euo pipefail
RUNS=${1:-300}
CPP_SRC="bench.cpp"
QC_SRC="bench.qc"
CPP_OUT="build/cpp"
QC_OUT="build/qc"
LOG_DIR="logs"
mkdir -p "$LOG_DIR" "$CPP_OUT" "$QC_OUT"
CPP_COMPILER="g++"
QC_COMPILER="./qc "
OPT_FLAGS=("O0" "O1" "O2" "O3" "Oz")
TIME_CMD="/usr/bin/time -v"
run_compiler_suite () {
    lang="$1"
    compiler="$2"
    src="$3"
    outdir="$4"
    logprefix="$5"
    echo ""
    echo "=============================="
    echo "$lang BENCHMARK"
    echo "=============================="
    for opt in "${OPT_FLAGS[@]}"; do
        echo ""
        echo ">>> Optimization: -$opt"
        BIN="$outdir/${lang}_${opt}"
        LOG="$LOG_DIR/${logprefix}_${opt}.log"
        CSV="$LOG_DIR/${logprefix}_${opt}.csv"
        echo "run,compile_ms,wall_ms,user_ms,sys_ms,exit_code,rss_kb" > "$CSV"
        for i in $(seq 1 "$RUNS"); do
            start_compile=$(date +%s%N)
            /usr/bin/time -v \
                $compiler -$opt "$src" -o "$BIN" \
                >> "$LOG" 2>&1
            end_compile=$(date +%s%N)
            compile_ms=$(( (end_compile - start_compile) / 1000000 ))
            run_output=$(
                { /usr/bin/time -f "%e,%U,%S,%M,%x" "$BIN" > /dev/null; } 2>&1
            )
            IFS=',' read -r elapsed user sys rss exit_code <<< "$run_output"
            wall_ms=$(awk "BEGIN { printf \"%.0f\", $elapsed * 1000 }")
            user_ms=$(awk "BEGIN { printf \"%.0f\", $user * 1000 }")
            sys_ms=$(awk "BEGIN { printf \"%.0f\", $sys * 1000 }")
            echo "$i,$compile_ms,$wall_ms,$user_ms,$sys_ms,$exit_code,$rss" >> "$CSV"
            echo "$lang -$opt run $i done"
        done
    done
}
run_compiler_suite "cpp" "$CPP_COMPILER" "$CPP_SRC" "$CPP_OUT" "cpp"
run_compiler_suite "qc" "$QC_COMPILER" "$QC_SRC" "$QC_OUT" "qc"
echo ""
echo "DONE. Raw logs in: logs/"
