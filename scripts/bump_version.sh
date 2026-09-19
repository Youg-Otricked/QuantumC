#!/usr/bin/env bash
set -e
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <current-version> <new-version>"
    exit 1
fi
OLD="$1"
NEW="$2"
FILES=(
    "version.txt"
    "compiler.h"
    "runtime.cpp"
    "compiler_run.cpp"
    "README.md"
)
for file in "${FILES[@]}"; do
    if [ ! -f "$file" ]; then
        echo "Warning: $file not found, skipping"
        continue
    fi
    sed -i "s/${OLD}/${NEW}/g" "$file"
    echo "Updated $file"
done
echo "Replaced '$OLD' with '$NEW'."

