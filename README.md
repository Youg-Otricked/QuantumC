# Quantum C (C⁴)
### The 4th Evolution of C
Check the web-demo out at [learnhardcode.dpdns.org/QuantumC/qc.html](https://learnhardcode.dpdns.org/QuantumC/qc.html).


**More Powerful Than Explosives™**

C⁴ combines the performance of C++, the ergonomics of C#, and the safety of Rust—without the 20 `#include` statements.

---

##  Features

-  **Modern Syntax** - Clean, intuitive, no boilerplate (other than main(obviously))
-  **Functions & Lambdas** - First-class functions with `fn` syntax
-  **Multi-Return Values** - Return multiple values without structs
-  **Type Safety** - Strong typing with `auto` inference
-  **Quantum Booleans** - Superposition of true/false
-  **F-Strings** - Python-style string interpolation

---

# Video

Go to the [docs](https://youg-otricked.github.io/QuantumC/)

##  Quick Start
Just install the binaries from the github OR
### Installation

**macOS:**
```bash
# Clone the repo
git clone https://github.com/Youg-Otricked/QuantumC
cd QuantumC

# Compile (one time)
clang++ *.cpp -o qc -std=c++20

# Run the demo
./qc -d
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
    g++ *.cpp -o qc -std=c++23 -fconstexpr-ops-limit=100000000
# Else
# Read while running the syntax guide
    ./qc -d
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
g++ *.cpp -o qc.exe -std=c++23 -lstdc++exp -fconstexpr-ops-limit=100000000 -Wa,-mbig-obj
# Run the syntax guide
# Note i have only tested on CMD. It might not work on pwrshell
qc.exe -d
```

---

# Language Guide
See [syntax.qc](syntax.qc) for a comprehensive interactive demo of all features!

---

# Development Status
strikthrough = done
Current Version: v5.0.2 = "User types (~~Struct~~, ~~enum~~, ~~class~~, ~~union~~, using aliases, ~~type/typedef~~, #include, interfaces, abstract classes)"

## Working:

Variables & Types (int, float, double, string, char, bool)
Operators & Expressions (including ** power operator!)
Control Flow (if/else, switch, while, for, foreach)
Functions with default parameters
Lambdas & higher-order functions
Multi-return values
F-strings
Constants (const)
Arrays
Lists
Spread syntax for arrays (@)
Length memeber for arrays + lists
Quantum Booleans (superposition!)
Quantum Logical Operators
Maps
Random
Long and Short
Structs
Union Types (TypeScript-style)
Enums
Class
Namespace
## Coming Soon:


Interfaces and more advanced OOP stuff
#include

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

### Q: Why is your cat GPU-sized?
**A:** Wrong FAQ. Also IDK
---

## Quantum Features

Quantum C is the **world's second quantum programming language _(at least, that more than like 2 people would ever say the name of(now that statement is true))_**, but the **first that doesn't require a $10M quantum computer!**

### Quantum Booleans
```cpp
qbool qb = both;  // Superposition! Both true AND false!

qif (qb) {
    println("True path");   // Executes!
} qelse {
    println("False path");  // ALSO executes!
}
```
---

## Quantum Logic Operators
```cpp
// Note these are not for normal booleans
&&& - Quantum AND
||| - Quantum OR
!! - Quantum NOT
^^ - Quantum XOR
=== - Quantum EQUAL
!== - Quantum NOT EQUAL
|&| - Collapse OR (convert to bool)
&|& - Collapse AND (convert to bool)
```
---

## Why Quantum C?

| **Feature**                   | **C++**    | **C#** | **Rust**       | **Quantum C**       |
|-------------------------------|------------|--------|----------------|---------------------|
| **Total Runtime**             | Slow       | Fast   | Slow           | (Near)**Instant**   |
| **Syntax**                    | Complex    | Clean  | Verbose        | **Minimal**         |
| **Memory safety**             | Manual     | GC     | Borrow checker | **C style!**        |
| **Quantum booleans**          | No         | No     | No             | **4 states!**       |
| **Multi-return**              | Structs    | Tuples | Tuples         | **Native**          |
| **Requires quantum computer** | No (What?) | Huh?   | WDYM           | NO!**(Unlike Q#!)** _(we get it microsoft, you wanted to be able to program your chip that sounds like a drug)_ |

---
Made by [Me](https://github.com/Youg-Otricked)

