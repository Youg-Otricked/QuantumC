# Quantum C (C⁴)
### The 4th Evolution of C

**More Powerful Than Explosives™**

C⁴ combines the performance of C++, the ergonomics of C#, and the safety of Rust—without the 20 `#include` statements.

---

##  Features

-  **Modern Syntax** - Clean, intuitive, no boilerplate (other than main(obviously))
-  **Functions & Lambdas** - First-class functions with `fn` syntax
-  **Multi-Return Values** - Return multiple values without structs(on normal funcitons. static and multi ret lambdas comming soon)
-  **Type Safety** - Strong typing with `auto` inference
-  **Quantum Booleans** - Coming soon: superposition of true/false
-  **F-Strings** - Python-style string interpolation

---

##  Quick Start

### Installation

**macOS:**
```bash
# Clone the repo
git clone https://github.com/Youg-Otricked/QuantumC
cd QuantumC

# Compile (one time)
clang++ *.cpp -o qc -std=c++23

# Run the demo
./qc syntax.qc
```
**Linux (ubuntu):**
```bash
# Clone the repo
git clone https://github.com/Youg-Otricked/QuantumC
# Move into it
cd QuantumC
# Check version
./qc -v
# If version is < current version (see development status):
# Compile
    g++ *.cpp -o qc -std=c++20 -fconstexpr-ops-limit=100000000
# Else
# Read while running the syntax guide
    ./qc syntax.qc
# Or enter the REPL
    ./qc
```
**Windows:**
```bash
# Clone the repo
git clone https://github.com/Youg-Otricked/QuantumC
# Move into it
cd QuantumC
# Compile
g++ *.cpp -o qc.exe -std=c++20 -fconstexpr-ops-limit=100000000
# Run the syntax guide
qc.exe syntax.qc
```

---

# Language Guide
See [syntax.qc](syntax.qc) for a comprehensive interactive demo of all features!

---

# Development Status
Current Version: v2.0 - "Multi Return functions and Lambdas (+ collection types)"

## Working:

Variables & Types (int, float, double, string, char, bool)
Operators & Expressions (including ** power operator!)
Control Flow (if/else, switch, while, for)
Functions with default parameters
Lambdas & higher-order functions
Multi-return values
F-strings
Constants (const)

## Coming Soon:

Static typing on lambda ret-types
Mulit return Lambdas
Arrays
Union Types (TypeScript-style)
Structs
Quantum Booleans (superposition!)

---

# Contributing
Found a bug? Have a feature request? Open an [Issue!](https://github.com/Youg-Otricked/QuantumC/issues)!

Want to contribute? PRs welcome!

---

## License
MIT License - See [LICENSE](./LICENSE.txt) for details

---

# (Semi) FAQ
### Q: Why “Quantum C”?

---

#### A:
Because it's the 4th evolution of C:

C - The original
C++ - Object-oriented and sharpend to a point (also added tons more features)
C# - Managed & modern (also by microsoft)
C⁴ - All of the above, none of the pain
Also, C4 is a powerful explosive. This language is more powerful than explosives.

Now Turing complete!

---
Made by [Me](https://github.com/Youg-Otricked)

