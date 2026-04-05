# Quantum C (C⁴)

### The 4th Evolution of C

## **THIS IS NOT A QCL**, it simply has Quantum-Inspired features.

Check the web-demo out at [learnhardcode.dpdns.org/QuantumC/qc.html](https://learnhardcode.dpdns.org/QuantumC/qc.html).
Or go to the docs right [here](https://youg-otricked.github.io/QuantumC/).

**More Powerful Than Explosives™**

C⁴ combines the performance of C++, the ergonomics of C#, and the safety of Rust—without the 20 `#include` statements.

---

## Features

- **Modern Syntax** - Clean, intuitive, no boilerplate (other than main(obviously))
- **Functions & Lambdas** - First-class functions with `fn` syntax for lambdas and `type name(args-type args-name)` syntax for normal functions
- **Multi-Return Values** - Return multiple values without structs
- **Type Safety** - Strong typing with `auto` inference
- **Quantum Booleans** - Superposition of true/false
- **F-Strings** - Python-style string interpolation
- **Special class methods** - Default initlization, representation, and evaluation methods along with operator overloads

---

# Video

Go to the [docs](https://youg-otricked.github.io/QuantumC/)

## Quick Start

Just install the binaries from the github OR

### Installation

After installing, or clone the repo directly then do

```bash
cd QuantumC
chmod +x install.sh
./install.sh
# type_your_sudo_password (it moves the binary into /usr/local/bin/ and also moves the stdli9b into /usr/local/QC/, along with the demo script)
# Now, you can type
qc [flags] (filepath)
# to run a file
# or
qc [flags]
# to enter the REPL
```

---

# Language Guide

See [syntax.qc](syntax.qc) for a comprehensive interactive demo of all features!

---

# Development Status

strikthrough = done
Current Version: v12.0.0 = "MMM"

## Feature Roadmap

| Category            | Feature                                                                | Status (WIP/Planned, Interpreted, or Done)                                     |
| ------------------- | ---------------------------------------------------------------------- | ------------------------------------------------------------------------------ | --- | -------------- | ---- |
| **Core Logic**      | Variables & Types (`int`, `float`, `double`, `string`, `char`, `bool`) | Done                                                                           |
|                     | Constants (`const`) & `auto` Inference                                 | Done                                                                           |
|                     | Long and Short types                                                   | Done                                                                           |
| **Operators**       | Standard Math & Expressions (includes `**` power operator)             | Done                                                                           |
|                     | Control Flow (`if/else`, `switch`, `while`, `for`, `foreach`)          | Done                                                                           |
| **Functions**       | Functions with Default Parameters                                      | Done                                                                           |
|                     | Lambdas & Higher-Order Functions                                       | Done                                                                           |
|                     | **Native Multi-Return Values**                                         | Done                                                                           |
| **Data Structures** | Arrays & Lists (with `.length` member)                                 | Done                                                                           |
|                     | Spread Syntax for Arrays (`@`)                                         | Done                                                                           |
|                     | Maps & Enums                                                           | Done                                                                           |
| **Quantum**         | **Quantum Booleans (Superposition!)**                                  | Done                                                                           |
|                     | **Quantum Logical Operators** (`&&&`, `                                |                                                                                |     | `, `!!`, etc.) | Done |
| **Advanced**        | Structs, Classes, & Namespaces                                         | Done                                                                           |
|                     | Union Types (TypeScript-style)                                         | Interpreted, Compiled has a few bugs with them, still mostly work in compiler. |
|                     | Advanced OOP & Operator Overloading                                    | Done                                                                           |
|                     | Manual Memory Management                                               | Interpreted                                                                    |
| **System**          | F-Strings (Python-style interpolation)                                 | Done                                                                           |
|                     | Random Number Generation                                               | Done                                                                           |
|                     | Stdlib Part 1 & 2                                                      | Done                                                                           |
| **Future**          | Stdlib Part 3                                                          | Coming Soon                                                                    |
|                     | Concurrency functions                                                  | Coming Soon                                                                    |
|                     | HTTP                                                                   | Coming Soon                                                                    |
|                     | Generics                                                               | Coming Soon                                                                    |

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

## **A:** Wrong FAQ. Also IDK

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

| **Feature**                   | **C++**    | **C#** | **Rust**       | **Quantum C**                                                                                                   |
| ----------------------------- | ---------- | ------ | -------------- | --------------------------------------------------------------------------------------------------------------- |
| **Total Runtime**             | Slow       | Medium   | Medium           | **Really** Fast                                                                                               |
| **Compile Time**              | Slow       | Medium   | Medium         | Medium                                                                                                          |
| **Runtime**                   | Fast       | Medium | Medium         | Fast |
| **Memory safety**             | Manual     | GC     | Borrow checker | **C style!**                                                                                                    |
| **Quantum booleans**          | No         | No     | No             | **4 states!**                                                                                                   |
| **Multi-return**              | Structs    | Tuples | Tuples         | **Native**                                                                                                      |

---

## Multi Return

```cpp
int, string GetStatus() {
    return 200, "Success";
}
int main() {
    int code, string alias = GetStatus();
    std::qout << f"Code: {code}, AKA: {alias}" << '\n';
    return 0;
}
```

## Manual Memory Managment

```cpp
int main() {
    int* ptr = malloc(sizeof("int"));
    *ptr = 42;
    println(*ptr);
    free(ptr);
}
```

## Include system
```cpp
namespace Exported {
    #include <Math, std> // std is a alias for /usr/share/bin
}

int main() {
    return Math::Max(1234, 432);
}
```

## Type collections and aliases

Define variables that can hold multiple types using a simple `|` syntax. The parser automatically distinguishes these from standard aliases:

```cpp
int main() {
    // A Union Type (TypeScript-style)
    type IdT = int | string;
    IdT id = 101;
    id = "A101"; // Perfectly valid

    // A Standard Alias
    type UserID = int;
    UserID myId = 5;
}
```

## Known limitations:

- You cannot use + style string concat on class instances if you arn't entending the + to call the operator+ method because it won't call repr, instead it will try and call operator+ on the class with a string argument. This limitation doesn't exist on fstrings though.
  Made by [Me](https://github.com/Youg-Otricked)
