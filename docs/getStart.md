<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Getting started
[Back to home](./index.md)

## Step 1: install the binarys or compile.
1. [ ] Either install the code from or download the code AND binarys from [Here](https://github.com/Youg-Otricked/QuantumC)
2. [ ] If compiling move on, otherwise, skip.
3. [ ] Run the following commands: 
```bash
# Linux

# Move into the cloned repo
cd QuantumC-master

# Compile
g++ *.cpp -o qc -std=c++23 -fconstexpr-ops-limit=100000000

# Run the version
./qc -v

# Run the demo
./qc -d

# Check flags with 
./qc -h
```

```bash
# Mac

# Move into the cloned repo
cd QuantumC-master

# Compile
clang++ *.cpp -o qc-macos -std=c++20 -stdlib=libc++

# Run the version
./qc -v

# Run the demo
./qc -d

# Check flags with 
./qc -h
```

```bash
# Windows

# Move into the cloned repo
cd QuantumC-master

# Compile
g++ *.cpp -o qc.exe -std=c++23 -fconstexpr-ops-limit=100000000 -Wa,-mbig-obj

# Run the version
qc.exe -v

# Run the demo
qc.exe -d

# Check flags with 
qc.exe -h
```
# You`re done and have installed Quantum C!
