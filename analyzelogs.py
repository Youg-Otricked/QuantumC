import pandas as pd
import glob
import os
files = glob.glob("logs/*.csv")
all_data = []
for f in files:
    df = pd.read_csv(f)
    name = os.path.basename(f).replace(".csv", "")
    compiler = "cpp" if "cpp" in name else "qc"
    opt = None
    for o in ["O0", "O1", "O2", "O3", "Oz"]:
        if o in name:
            opt = o
            break
    df["compiler"] = compiler
    df["opt"] = opt
    df["source_file"] = name
    all_data.append(df)
data = pd.concat(all_data, ignore_index=True)
print("OVERALL STATS (ALL DATA)")
print("Total runs:", len(data))
print("\nWALL TIME")
print("Median:", data["wall_ms"].median())
print("Mean:", data["wall_ms"].mean())
print("P95:", data["wall_ms"].quantile(0.95))
print("\nUSER CPU TIME")
print("Median:", data["user_ms"].median())
print("Mean:", data["user_ms"].mean())
print("P95:", data["user_ms"].quantile(0.95))
print("\nCOMPILE TIME")
print("Median:", data["compile_ms"].median())
print("Mean:", data["compile_ms"].mean())
print("P95:", data["compile_ms"].quantile(0.95))
print("\nRSS")
print("Median:", data["rss_kb"].median())
print("Mean:", data["rss_kb"].mean())
print("\nPER COMPILER")
print(
    data.groupby("compiler")[
        ["wall_ms", "user_ms", "compile_ms", "rss_kb"]
    ].median()
)
print("\nPER OPT LEVEL")
print(
    data.groupby("opt")[
        ["wall_ms", "user_ms", "compile_ms", "rss_kb"]
    ].median()
)
print("\nCOMPILER × OPT LEVEL")
print(
    data.groupby(["compiler", "opt"])[
        ["wall_ms", "user_ms", "compile_ms", "rss_kb"]
    ].median()
)
print("\nSTDDEV (runtime stability)")
print(
    data.groupby(["compiler", "opt"])[
        ["wall_ms", "user_ms"]
    ].std()
)
