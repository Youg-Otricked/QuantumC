#!/bin/bash

QC_LIB="$HOME/.qc/lib"

if [ ! -f "./stdlib.qc" ]; then
    echo "Error: ./stdlib.qc not found in current directory"
    exit 1
fi

mkdir -p "$QC_LIB"

echo "Installing new stdlib..."
cp ./stdlib.qc "$QC_LIB/stdlib.qc"
cp ./syntax.qc "$QC_LIB/syntax.qc" 2>/dev/null || true

echo "stdlib.qc updated successfully!"
echo "Location: $QC_LIB"