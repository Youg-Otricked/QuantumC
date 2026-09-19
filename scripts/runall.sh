for file in ./tests/*.qc; do
    echo "Processing file: $file"
    ./qc $file
done
for file in *.qc; do
    echo "Processing file: $file"
    ./qc $file
done