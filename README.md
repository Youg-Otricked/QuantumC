# Quantum C (C⁴)

### The 4th Evolution of C

## **THIS IS NOT A QCL**, it simply has Quantum-Inspired features.

Check the web-demo out at [learnhardcode.dpdns.org/QuantumC/qc.html](https://learnhardcode.dpdns.org/QuantumC/qc.html).
Or go to the docs right [here](https://youg-otricked.github.io/QuantumC/).

**More Powerful Than Explosives™**

C⁴ combines the performance of C++, the ergonomics of Rust, and the cleaness of Zig—without the 20 `#include` statements.

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
Current Version: v0.15.0 = "Compiler Is Mostly Done" (aparantly i've been using 15 instead of 0.15 OOPS)

## Feature Roadmap

| Category            | Feature                                                                | Status      |
| ------------------- | ---------------------------------------------------------------------- | ----------- |
| **Core Logic**      | Variables & Types (`int`, `float`, `double`, `string`, `char`, `bool`) | Done        |
|                     | Constants (`const`) & `auto` Inference                                 | Done        |
|                     | Long and Short types                                                   | Done        |
| **Operators**       | Standard Math & Expressions (includes `**` power operator)             | Done        |
|                     | Control Flow (`if/else`, `switch`, `while`, `for`, `foreach`)          | Done        |
| **Functions**       | Functions with Default Parameters                                      | Done        |
|                     | Lambdas & Higher-Order Functions                                       | Done        |
|                     | **Native Multi-Return Values**                                         | Done        |
| **Data Structures** | Arrays & Lists (with `.length` member)                                 | Done        |
|                     | Spread Syntax for Arrays (`@`)                                         | Done        |
|                     | Maps & Enums                                                           | Done        |
| **Quantum**         | **Quantum Booleans (Superposition!)**                                  | Done        |
|                     | **Quantum Logical Operators** (`&&&`, `\|\|\| `, `!!`, etc.)           | Done        |
| **Advanced**        | Structs, Classes, & Namespaces                                         | Done        |
|                     | Union Types (TypeScript-style)                                         | DONE        |
|                     | Advanced OOP & Operator Overloading                                    | Done        |
|                     | Manual Memory Management                                               | DONE!       |
| **System**          | F-Strings (Python-style interpolation)                                 | Done        |
|                     | Random Number Generation                                               | Done        |
|                     | Stdlib Part 1 & 2                                                      | Done        |
| **Future**          | Stdlib Part 3                                                          | Coming Soon |
|                     | Concurrency functions                                                  | Coming Soon |
|                     | HTTP                                                                   | Coming Soon |
|                     | Generics                                                               | Coming Soon |
|                     | Passable code blocks, eg `void example() code { code.eval() }`         | Coming Soon |
|                     | Extern                                                                 | Coming Soon |
|                     | Bitwise Logic                                                          | Coming Soon |
|                     | Reallly fancy operator overloads                                       | Coming Soon |

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

### Q: How many Seg-Faults have you delt with.

#### A;

The answer would integer overflow.

### Quantum Booleans

```cpp
qbool qb = both;  // Superposition! Both true AND false!

qif (qb) {
    qout("True path");   // Executes!
} qelse {
    qout("False path");  // ALSO executes!
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

| **Feature**          | **C++** | **Zig** | **Rust**       | **Quantum C**   |
| -------------------- | ------- | ------- | -------------- | --------------- |
| **Total Runtime**    | Slow    | Medium  | Medium         | **Really** Fast |
| **Compile Time**     | Slow    | Medium  | Medium         | Medium          |
| **Runtime**          | Fast    | Medium  | Medium         | Fast            |
| **Memory safety**    | Manual  | GPA     | Borrow checker | **C style!**    |
| **Quantum booleans** | No      | No      | No             | **4 states!**   |
| **Multi-return**     | Structs | Tuples  | Tuples         | **Native**      |

---

## Multi Return

```cpp
int, string GetStatus() {
    return 200, "Success";
}
int main() {
    int code, string alias = GetStatus();
    qout("%s", f"Code: {code}, AKA: {alias}\n");
    return 0;
}
```

## Manual Memory Managment

```cpp
int main() {
    int* ptr = malloc(sizeof "int");
    *ptr = 42;
    qout("%p", ptr); 
    free(ptr);
}
```

## Include system

```cpp
namespace Exported { // Includes go inside exported to keep dependencys working. It's auto merged with includers files on include, so lets say a includes b and b includes c, the actual order is a includes bs exported, then bs exported includes cs exported, nothing's in cs exported, so b includes c, then the chain has been resolved so a includes b. The compiled file would look somthing like
/*
namespace Exported (file a)
namespace Exported (file b)
namespace Exported (file c)
<imported namespace from file c>
<imported namespace from file b>
(rest of code)
*/
    #include <Math, std> // std is a alias for ~/.qc/lib/stdlib.qc. This line imports the Math namespace from the standered library.
}

int main() {
    return Math::Max(1234, 432); // Using the math namespace.
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

## Ideals

QuantumC follows 4 core rules:

- Forced Cleanliness: Your code should and must be readable. Clean is not defined as 'Convinient for language', it means what it should be. Clean is not a "pythonic" equievalant, it is self explanitory.
- Your Memory, Your Problem: QuantumC does not stop you from doing somthing cool or implementing your dangerous ideas. QuantumC also doesn't stop you from making dangerous mistakes. Quantum C is strongly typed, but union types are designed to be ergonomic rather than restrictive. Unlike Rust or TypeScript, Quantum C does not force exhaustive narrowing before every union operation.
- No Hiding: QuantumC is an explicit language: Your code does what it looks like it does. Nothing is hidden inside the parser yet pretends to be stdlib, nothing is hidden away in some back catacoamb. If it is a intrinsic, it says it is.
- No Excessive Syntax: No capture lists on lambdas, no templates, no infinite <>, no Rust "bird droppings", no ! and @ everywhere.
  Made by [Me](https://github.com/Youg-Otricked)
