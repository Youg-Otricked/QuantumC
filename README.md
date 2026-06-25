# QuantumC (C⁴)

### The 4th Evolution of C

## **THIS IS NOT A QCL**. It does not simulate quantum logic. It does not run on a quantum computer. It is a normal programming language.

Check the web-demo out at [learnhardcode.dpdns.org/QuantumC/qc.html](https://learnhardcode.dpdns.org/QuantumC/qc.html).
Or go to the docs right [here](https://youg-otricked.github.io/QuantumC/).

**More Powerful Than Explosives™**

C⁴ combines the performance of C++, the ergonomics of Rust, and the cleanliness of Zig—without the 20 `#include` statements.

---

## What is QuantumC?
QuantumC (C⁴/C^4) is a compiled, statically typed C-Style Systems programming language, focusing on clean code and low global scope pollution.
## Features

- **Modern Syntax** - Clean, intuitive, no boilerplate (other than main)
- **Functions & Lambdas** - First-class functions with `fn` syntax for lambdas and `type name(args-type args-name)` syntax for normal functions
- **Multi-Return Values** - Return multiple values without structs
- **Type Safety** - Strong typing with `auto` inference
- **Quantum Booleans** - Superposition of true/false
- **F-Strings** - Python-style string interpolation
- **Special class methods** - Default initialization, representation, and evaluation methods along with operator overloads

---

# Video

Go to the [docs](https://youg-otricked.github.io/QuantumC/)

## Quick Start

Just install the binaries from the github, use the [Package & Version Manager](https://github.com/Youg-Otricked/quantum-c-version-manager) OR

### Installation

After cloning the repo to your machine, run

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

# Development Status

Current Version: v0.17.71 = "The Include System Refactor"

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
| **Advanced**        | Structs, Classes, & Namespaces                                         | Done        |
|                     | Union Types (TypeScript-style)                                         | Done        |
|                     | Advanced OOP & Operator Overloading                                    | Done        |
|                     | Manual Memory Management                                               | Done        |
| **System**          | F-Strings (Python-style interpolation)                                 | Done        |
|                     | Random Number Generation                                               | Done        |
|                     | Stdlib Part 1 & 2                                                      | Done        |
| **Future**          | Stdlib Part 3                                                          | Planned     |
|                     | Concurrency functions                                                  | Planned     |
|                     | Inline ASM                                                             | Done        |
|                     | HTTP                                                                   | Planned     |
|                     | Generics                                                               | Planned     |
|                     | Passable code blocks, eg `void example() code { code.eval() }`         | Planned     |
|                     | Extern                                                                 | Planned     |
|                     | Bitwise Logic                                                          | Done        |
|                     | Really fancy operator overloads                                        | Planned     |
|                     | Try/Catch and `throw`                                                  | Planned     |

See the full list of remaining features in the [roadmap](https://github.com/Youg-Otricked/QuantumC/blob/master/roadmap.md)
# Contributing

Found a bug? Have a feature request? Open an [Issue!](https://github.com/Youg-Otricked/QuantumC/issues)!

Want to contribute? PRs welcome!

---
 
## License

MIT License - See [LICENSE](./LICENSE.txt) for details

---

# (Semi) FAQ

### Q: Why “QuantumC”?

---

#### A:

Because it's the 4th evolution of C:

C - The original
C++ - Object-oriented and sharpened to a point (also added tons more features)
C# - Managed & modern (also by microsoft)
C⁴ - All of the above, none of the pain
There are 2 other meanings that would take too much space to explain.
Now Turing complete!


### "Quantum" Booleans (i2)

```cpp
qbool qb = both;  // Superposition! Both true AND false!

qif (qb &&* qtrue /* evaluates to both */) {
    qout("True path");   // Executes!
} qelse {
    qout("False path");  // ALSO executes!
}
```

---

---


## Manual Memory Management

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
namespace Exported {
/*
Exported namespaces are merged during include resolution.
See the include-system docs for full details.
*/
    #include <Math, std> // std is an alias for ~/.qc/lib/stdlib.qc. This line imports the Math namespace from the standard library.
}

int main() {
    return Math::Max(1234, 432); // Using the math namespace.
}
```
Want to learn more? Check out the [docs for it](https://youg-otricked.github.io/QuantumC/include.html)
## Why QuantumC?

| **Feature**                 | **C++** | **Zig** | **Rust**       | **QuantumC**   |
| --------------------------- | ------- | ------- | -------------- | --------------- |
| **Total Runtime**           | Medium  | Medium  | Medium         | Medium          |
| **Compile Time (relative)** | Slow    | Medium  | Medium         | Medium          |
| **Runtime**                 | Fast    | Medium  | Medium         | Fast            |
| **Memory safety**           | Manual  | GPA     | Borrow checker | Manual          |
| **Multi-return**            | Structs | Tuples  | Tuples         | **Native**      |

QuantumC has comparable performance to C++, with faster compile times, and similar amounts of QOL features to languages like Zig.

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

## C interop & inline ASM

Extern "C" is the only supported extern style, and thus no string is needed to say where you are externing to.
```cpp
extern:
int add(int a, int b) {
    return a + b;
}
:extern
```
Extern is only for _externalizing_ api. To use _foreign_ code, you must put it in a `foreign` block.
```cpp
foreign:
int do_some_c_stuff(int x);
:foreign
```

---
The QuantumC inline ASM syntax is like a simplified version of the GCC syntax:

```cpp
inline(R"(
mov rax, 1
mov rdi, 1 
mov rsi, $0r ; argument 1 (Hello, World!) 
mov rdx, $1r ; argument 2 (14)
syscall
)"/* your inline asm string */, "Hello, World", 14, "~{rax}~{rdi}~{rsi}~{rdx}" /* clobbers */);  
```
You can also use AT&T ASM syntax by making sure the first 5 characters of your ASM string are 
```asm
; ATT
```
## Variadic arguments

QuantumC variadic arguments look like this:
```cpp
int add_all(...args) {
    int res = 0;
    while (!is_empty(args)) {
        res += next(args, "int");
    }
    return res;
}
```
`args` is a variadic argument (hence the `...`), which can be passed any amount of parameters.
`is_empty` is a runtime compiler intrinsic that takes a variadic arg-list and returns if it is empty.
`next` is a runtime compiler intrinsic that takes a variadic arg-list and a string holding the stringified expected type and returns the next element in the arg list casted to that type.

You may use C-Style variadic arguments too, but _only in foreign blocks_.
```cpp
foreign:
void printf(char* fmt, ...);
:foreign
```

## Bitwise logic

QuantumC has all the standard bitwise logic operators, however it has a non-standard XOR token.
The Bitwise XOR operator in C^4 is `$`. It is `$` becuase ^ and ^^ are already used tokens, and C^4 avoids repeating tokens to improve quick readability.
QuantumC also has a special operator for _logical_ right shift: :>. This is because it allows avoiding constantly casting between signed and unsigned integer types unlike C++'s "arithmetic if signed, logical if unsigned"

## Preformance Comparison:

Comparison output & `.csv` files are located in the `logs` directory. 

## Known limitations:

- You cannot use + style string concat on class instances if you aren't intending the + to call the operator+ method because it won't call repr, instead it will try and call operator+ on the class with a string argument. This limitation doesn't exist on fstrings though.

## Ideals

QuantumC follows 4 core rules:

- Forced Cleanliness: Your code should and must be readable. Clean is not defined as 'Convenient for language', it means what it should be. Clean is not a "pythonic" equivalent, it is self-explanatory.
- Your Memory, Your Problem: QuantumC does not stop you from doing something cool or implementing your dangerous ideas. QuantumC also doesn't stop you from making dangerous mistakes. QuantumC is strongly typed, but union types are designed to be ergonomic rather than restrictive. Unlike Rust or TypeScript, QuantumC does not force exhaustive narrowing before every union operation. I will give you a loaded shotgun. If you blow your leg off, don't blame the gunsmith.
- No Hiding: QuantumC is an explicit language: Your code does what it looks like it does. Nothing is hidden inside the parser yet pretends to be stdlib, nothing is hidden away in some back catacomb. If it is an intrinsic, it says it is.
- No Excessive Syntax: No capture lists on lambdas, no templates, no infinite <>, no Rust "bird droppings", no ! and @ everywhere.

## Compiler Architecture

QuantumC uses a classic multi-pass compilation pipeline:
1. **Lexical Analysis / Preprocessing:** Custom scanner with support for multi-file include resolution.
2. **AST Parsing:** Recursive descent parser generating a strongly typed Abstract Syntax Tree.
3. **Type Checking & Semantic Analysis:** Resolves user-defined types, namespaces, and TypeScript-style union types. The unique thing is that this pass is _merged with the compilation/codegen phase_
4. **Intermediate Representation (IR):** Generates LLVM IR. Target-aware pointer arithmetic is achieved dynamically via target-specific DataLayout queries.
5. **Codegen:** Emits native platform object files (`.o`) or WebAssembly binaries via LLVM's target machines.
  Made by [Luca Fazio](https://github.com/Youg-Otricked)

