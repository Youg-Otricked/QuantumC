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
- **Special class methods** - Representation, evaluation, and operator overloading

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

# Sections

- [Roadmap](#feature-roadmap)
- [Manual Memory Management](#manual-memory-management)
- [Include System](#include-system)
- [Why QuantumC?](#why-quantumc)
- [Code Conventions](#conventions)
- [Type collections and aliases](#type-collections-and-aliases)
- [Systems-y stuff](#c-interop-and-inline-asm)
- [Generics and Iterators](#generics)
- [Misc.](#performance-comparison)

---

# Development Status

Current Version: x0.18.0 = "Generics"
Next Version: x0.18.1 = "Generics (part 2)"

## Feature Roadmap

| Category            | Feature                                                                | Status      |
| ------------------- | ---------------------------------------------------------------------- | ----------- |
| **Core Logic**      | Variables & Types (`int`, `float`, `double`, `string`, `char`, `bool`) | Done        |
|                     | Constants (`const`) & `auto` Inference                                 | Done        |
|                     | Long and Short types                                                   | Done        |
| **Operators**       | Standard Math & Expressions (includes `#^` power operator)             | Done        |
|                     | Control Flow (`if/else`, `switch`, `while`, `for`, `foreach`)          | Done        |
| **Functions**       | Functions with Default Parameters                                      | Done        |
|                     | Lambdas & Higher-Order Functions                                       | Done        |
|                     | **Native Multi-Return Values**                                         | Done        |
| **Data Structures** | Arrays (with `.length` member)                                         | Done        |
|                     | Spread Syntax for Arrays (`@`)                                         | Done        |
|                     | Enums                                                                  | Done        |
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
|                     | Generics                                                               |             |
|                     |     Classes                                                            | Done        |
|                     |     Structs                                                            | Planned     |
|                     |     Unions                                                             | Planned     |
|                     |     Functions & Methods                                                | Planned     |
|                     |     Variadic                                                           | Planned     |
|                     | Passable code blocks, eg `void example() code { code.eval() }`         | Planned     |
|                     | Extern                                                                 | Done        |
|                     | Bitwise Logic                                                          | Done        |
|                     | Really fancy operator overloads                                        | Planned     |
|                     | Try/Catch and `throw`                                                  | Planned     |
|                     | Error message quality and helpfulness upgrade                          | Planned     |

See the full list of remaining features in the [roadmap](https://github.com/Youg-Otricked/QuantumC/blob/master/roadmap.md)
# Contributing

Found a bug? Have a feature request? Open an [Issue!](https://github.com/Youg-Otricked/QuantumC/issues)!

Want to contribute? PRs welcome!

---
 
## License

MIT License - See [LICENSE](./LICENSE.txt) for details

---

# (Semi) FAQ

### Q: Why “C^4”?

---

#### A:

Because it's the 4th evolution of C:

C - The original
C++ - Object-oriented and sharpened to a point (also added tons more features)
C# - Managed & modern (also by microsoft)
C⁴ - All of the above, none of the pain
There are 2 other meanings that would take too much space to explain.
Now Turing complete!

---

### i2 Primitive Type

```cpp
qbool qb = both;
qif (qb && qtrue /* evaluates to both */) {
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

Namespaces can also declare dependencies on other namespaces in the same file
using `#depends`, ensuring includers automatically see required types even if
they only explicitly included one namespace from that file:

```cpp
#depends(x: y)
namespace x { /* uses y::Something internally */ }
namespace y { /* ... */ }
```

Want to learn more? Check out the [docs for it](https://youg-otricked.github.io/QuantumC/include.html)

---
## Why QuantumC?

| **Feature**                 | **C++**              | **Zig**          | **Rust**         | **QuantumC**        |
| --------------------------- | -------------------- | ---------------- | ---------------- | ------------------- |
| **Total Runtime**           | Medium               | Medium           | Medium           | Medium              |
| **Compile Time (relative)** | Slow                 | Medium           | Medium           | Medium              |
| **Runtime**                 | Fast                 | Medium           | Medium           | Fast                |
| **Memory safety**           | Manual               | GPA              | Borrow checker   | Manual              |
| **Multi-return**            | Structs              | Tuples           | Tuples           | **Native**          |
| **Generics**                | Templates + Concepts | Type as Argument | Trait Based      | Constraint-Based    |

QuantumC has comparable performance to C++, with faster compile times, and similar amounts of QOL features to languages like Zig.

---

## Conventions

QuantumC has rather unique naming conventions:

| **Type**                               | **Convention**         | **Why?**                                                                                                                     |
| -------------------------------------- | ---------------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| **Variables**                          | `snake_case`           | It's familiar to Python devs who changed their ways, C++, C, Zig, Go, and Rust devs.                                         |
| **Functions**                          | `camelCase`            | It allows for instant knowledge between if an identifier is a var, or function (lambdas use var casing, not function casing) |
| **User Types**                         | `PascalCase`           | It is common across basically every programming language.                                                                    |
| **Constants**                          | `SCREAMING_SNAKE_CASE` | Same as above.                                                                                                               |
| **Private Member Variables**           | `__snake_case`         | Variable case prepended with __. Most underscores.                                                                           |
| **Protected Member Variables**         | `_snake_case`          | Less underscores.                                                                                                            |
| **Private Methods**                    | `__camelCase`          | Unique casing, more underscores.                                                                                             |
| **Private Methods**                    | `camel_Snake_Case`     | Function casing, more underscores.                                                                                           |
| **Namespaces**                         | `PascalCase`           | Same as user types.                                                                                                          |
| **Namespaces Not Meant For Inclusion** | `Pascal_Snake_Case`    | Unique casing style, more underscores, you have to be trying to include this.                                                |
| **Global Scope Functions**             | `camel_Snake_Case`     | Unique casing style, more underscores, similar to private methods is intentional, because global scope cannot be included.   |
| **Methods Used By Compiler**           | `_camelCase`           | Different from everything else. (these methods are iterators and stuff. Methods you define and compiler uses)                | 
| **Compiler Reserved**                  | `_qc_, __qc_ and qc_`  | Unique, hard to use accidently                                                                                               |


Max line size is around 120 _relative to your starting indentation_, tabs or spaces, lf newlines, comments are `//`, doc comments are `///`, and top-level doc comments are `//!`. File paths are unquoted, everything other than main should go in a namespace (not a strict rule, just a ideal, no need to follow), and namespaces should fit the following rules:

1. Namespaces should do one thing well, similar to the UNIX philosophy, 
2. Namespaces should have either:
        * one type (or group of TIGHTLY related types, eg bigints) and their core helpers,
        * above + namespaces containing extra helpers
        * helper functions / utility functions (think a `Math` namespace with log, cos...)
        * OR anything if directly mapping  C/C++/Zig/Rust code to C^4
3. Types in namespaces should have short names: The namespace should have the longer name
        e.g.
```qc
namespace Array {
    class Arr<T, int S = 0> {
        ...
    }
}
```
All *'s in pointer types stick to the type other than the last, E.G.
```
int** *x;
```
QuantumC naming conventions are designed to make code readable without requiring the reader to inspect library code. Names should provide immediate context.
My rule: `RTFM` once, not `RTMSCE5S` (Read The Manual and Source Code Every 5 Seconds), and these conventions make things hard to forget or miss-type, unlike C/C++ where every single library uses entirely different conventions.

Example:
```
namespace Network {
    class Client {
        string server_name;

        void connectToServer() {
            ...
        }
    }
}
namespace API_Keys_In_Plain_Text { // Intentionally formatted as a non-inclusion namespace.
    // Sure, you may not want to type all of that. That means your users absolutely don't.
    ...
}
```

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

---

## C interop and inline ASM

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

QuantumC has all the standard bitwise logic operators, however it has a non-standard XOR, and Right-Shift token.
The Bitwise XOR operator in C^4 is `$`. It is `$` becuase ^ and ^^ are already used tokens, and C^4 avoids repeating tokens to improve quick readability.
The same logic applys for right-shift: `|>` is the right-shift token, becuase it allows the parser to immediately determine:
```
Node<Vector<X>> // Is this RSHIFT or ending generics?
```
This is easy to determine (becuase it would be illegal for rshift to be there), however using this non-normal rshift operator allows it to be instant because:
```
Node<Vector<X>> // This is unrelated to RSHIFT
```
QuantumC also has a special operator for _logical_ right shift: :>. This is because it allows avoiding constantly casting between signed and unsigned integer types unlike C++'s "arithmetic if signed, logical if unsigned"

2 more unique bitwise things QuantumC does:

1. Builtin rotations: `<<<` and `|>>` and `LROT` and `RROT`, allowing 1 instruction rotations instead of 6+.
2. I did what we were all thinking and too scared to say: + and - should have lower priority than shifts. `3 << 3 + 2 == 26` 
    
## Generics

QuantumC generics have rather simple syntax:
```
class C<T> {
    T x;
    C() {
    }
}
int main() {
    C<int> thing = C();
}
```
Generics are allowed on `struct`s, `class`es, unions, functions, and methods.
The unique thing about QuantumC's generics are its constraint system:
The constraint system follows this syntax:
```
<T([constraint]:[[!]<[typename]'|'...>]>
```
Main constraints are as follows:
```
usertype: non-primitive type
primitive: primitive type
pointer: any pointer type
numeric: any numeric type
```
So
```
<T(numeric:)>
```
Can be any number type.
The subconstraint system is like this:
```
<T(:!int|string)>
```
This means "T can be any type other than int or string".
The ! means not anything in this set and the type|type means these types.
QuantumC also has non-type generic parameters.
```
<int S> // S is a non-type generic parameter (a compile time int)
```

Classes currently are the only thing to have generics.

In Rust, 
```
<T(numeric:)>
```
Would be
```
<T: std::ops::Add<Output = T> + std::ops::Sub<Output = T> + std::ops::Mul<Output = T> + std::ops::Div<Output = T> + PartialOrd + Copy>
```
And in C++, it would be
```
template <typename T>
requires std::is_arithmetic_v<T>
T
```
or in old SFINAE C++
```
template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
T
```
And in Zig:
```
...(comptime T: type, ...) ... {
    switch (@typeInfo(T)) {
        .Int, .Float => ...,
        else => @compileError("T must be numeric"),
    }
}
```

## Iterators

Iterators work as follows:
The class you want to iterate must define the following method:
```qc
MyIterator _begin() // Returns a iterator to the begining of the class
```
`_end` is optional, and returns a iterator to the end of the class.
The iterator itself MUST define the following 2 methods:
```qc
bool _atEnd() // Returns true if there is nothing left to iterate
T _next() // Returns the current value then moves to the next
```
and may define the following recommended extra methods:
```qc
bool _atStart() // Returns true if the itertor is currently at index 0
T _prev() // Returns the element at current index -- and decrements current index
void _moveTo(whateveryouwant idx) // sets index to idx
```

Example:
```qc
class ArrayIterator<T> {
    T* data;
    int size;
    int current_index;
    ArrayIterator(T* data, int size, bool is_end) {
        this.data = data;
        this.size = size;
        this.current_index = ternary(is_end, size - 1, 0);
    }
    bool _atEnd() {
        return this.size <= this.current_index;
    }
    T _next() {
        if (!this._atEnd()) {
            return this.data[this.current_index++];
        }
        return this.data[this.current_index];
    } 
    bool _atStart() {
        return this.current_index <= 0;
    }
    T _prev() {
        if (!this._atStart()) {
            return this.data[--this.current_index];
        }
        return this.data[this.current_index];
    }
    void _moveTo(int index) {
        if (index >= this.size) {
            index = this.size - 1;
        } else if (index < 0) {
            index = 0;
        }
        this.current_index = index;
    }
}
class Array<T, int S = 0> {
    T* data;
    int size;
    Array() {
        this.data = nullptr;
        this.size = 0;
    }
    void operator[]=(T* data, int length) {
        if (length > S) {
            this.size = length;
        } else {
            this.size = S;
        }
        this.data = malloc(sizeof "T" * this.size);
        for (int i = 0; i < this.size; i++) {
            this.data[i] = data[i];
        }
    }
    T operator[](int index) {
        return this.data[index];
    }
    ArrayIterator<T> _begin() {
        return ArrayIterator<T>(this.data, this.size, false);
    }
    ArrayIterator<T> _end() {
        return ArrayIterator<T>(this.data, this.size, true);
    }
}
```

The standard library collections have iterators in the structure of this:
```qc
namespace Array
    namespace Iterator {
        class It {
            ...
        }
    }
    class Arr {
        Iterator::It _begin() {
            ...
        }
        ...
    }
}
```

## Simple File Example

```qc
namespace Exported {
    #include<Vector, std>
}
int main() {
    Vector::Vec<int> my_vec = [1, 2, 3];
    my_vec.push(123);
    qout("%i", my_vec[2]);
    return 0;
}
```

---

## Performance Comparison

Comparison output and `.csv` files are available in the `logs` directory.

The benchmark compares generated QC code against equivalent C++ code across multiple optimization levels.

> Note: Due to a measurement precision issue in the benchmark harness, `-O1` and `-Oz` results could not be measured reliably.

Measured results:
- `-O0`: QC performance is approximately 2× faster than the equivalent C++ benchmark.
- `-O2` / `-O3`: QC performance is approximately 2× slower than the equivalent C++ benchmark.

The benchmark uses a CPU-heavy workload designed to compare generated code performance.

## Known limitations:

- `foreach` over class-typed fields (e.g. iterating a generic container stored as this.field) may not resolve correctly in all cases — actively being hardened.
- `auto` param and returning functions and methods are rather finiky, and such, unrecommended

## Standard Library Namespaces:

```
Vector
List
Array
AdvQBool
Math
Utils
OSInterop
```

## Ideals

QuantumC follows 4 core rules:

- Forced Cleanliness: Your code should and must be readable. Clean is not defined as 'Convenient for language', it means what it should be. Clean is not a "pythonic" equivalent, it is self-explanatory.
- Your Memory, Your Problem: QuantumC does not stop you from doing something cool or implementing your dangerous ideas. QuantumC also doesn't stop you from making dangerous mistakes. QuantumC is strongly typed, but union types are designed to be ergonomic rather than restrictive. Unlike Rust or TypeScript, QuantumC does not force exhaustive narrowing before every union operation. I will give you a loaded shotgun. If you blow your leg off, don't blame the gunsmith.
- No Hiding: QuantumC is an explicit language: Your code does what it looks like it does. Nothing is hidden inside the parser yet pretends to be stdlib, nothing is hidden away in some back catacomb. If it is an intrinsic, it says it is.
- No Excessive Syntax: No capture lists on lambdas, no templates, no infinite <>, no Rust "bird droppings", no ! and @ everywhere.

## Compiler Architecture

QuantumC uses a classic multi-pass compilation pipeline:
1. **Lexical Analysis / Preprocessing:** Custom lexer converts text to tokens in one loop.
2. **AST Parsing:** Recursive descent parser generating a strongly typed Abstract Syntax Tree.
3. **Type Checking & Semantic Analysis:** Resolves user-defined types, namespaces, and TypeScript-style union types. The unique thing is that this pass is _merged with the compilation/codegen phase_
4. **Intermediate Representation (IR):** Generates LLVM IR. Target-aware pointer arithmetic is achieved dynamically via target-specific DataLayout queries.
5. **Codegen:** Emits native platform object files (`.o`) or WebAssembly binaries via LLVM's target machines.
  Made by [Luca Fazio](https://github.com/Youg-Otricked)

