import csv
import glob
import statistics
for f in sorted(glob.glob("logs/*.csv")):
    values = []
    with open(f) as file:
        reader = csv.DictReader(file)
        for row in reader:
            values.append(float(row["wall_ms"]))
            values.sort()
        median = statistics.median(values)
        mean = statistics.mean(values)
        std = statistics.stdev(values)
        print("\n", f)
        print("median:", median, "ms")
        print("mean:", mean, "ms")
        print("std:", std, "ms")
