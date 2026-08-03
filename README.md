# QuantumC (C⁴/C^4)

### The 4th Evolution of C

QuantumC (C⁴) is a general-purpose systems programming language.
It is **not** a quantum computing language. It does not simulate quantum logic,
compile to quantum circuits, or run on quantum hardware. QuantumC (C^4) is unrelated to the C99-to-OpenQASM compiler, QuantumC

```qc
int main() {
    `qout("Hello, World!");
    return 0;
}
```

Check the web-demo out at [learnhardcode.dpdns.org/QuantumC/qc.html](https://learnhardcode.dpdns.org/QuantumC/qc.html).
Or go to the docs right [here](https://youg-otricked.github.io/QuantumC/).

**More Powerful Than Explosives™**/j
C⁴ combines explicitness and simplicity to produce readable code, improving both DX and UX. Code should still make sense next week, even to the person who wrote it.

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

#### Dependencies

You must have `clang` installed (or the path /usr/lib/clang/<VERSION>/include/unwind.h must exist)

---

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

# Versioning Scheme

QuantumC uses the following versioning scheme:
`cMa.Mo.MiP`
Where `c` is critical (massive additions, such as the compiler being added), `Ma` being major versions, tracking large collections of features, `Mo` being moderate versions, tracking collections of similar features, `Mi` being minor versions, which track individual feature milestones within the current moderate version's theme., and `P` being the patch version. 
For the version
`x1.2.34`
`c` = `x`
`Ma` = `1`
`Mo` = `2`
`Mi` = `3`
`P` = `4`

P is ommited if it is 0.
Critical versions represent the largest generational milestones in QuantumC's development.

v = Interpreter
x = Compiler (Current)
f = Feature-complete compiler
s = Self-hosted compiler

Critical versions are intentionally rare and denote architectural milestones,
not language features.

Development toward future critical versions may begin before the current
critical version is complete. Multiple critical generations may therefore
be in development simultaneously.

Minor (Mi) is always a single decimal digit (0-9). Once a minor version reaches 9, the next release increments the moderate version instead.

Unlike semantic versioning, QuantumC versions describe the scale and category of language evolution rather than API compatibility.
# Development Status

Current Version: x0.24.323 = "Various bugfixes"
Next Version: x0.25.0 = "Token/(maybe)Ident primitive types"

# Current Version Highlights

```text
Critical
└─ Added Compiler

Major
└─ N/A

Moderate
└─ Making the compiler feel more "Native"

Minor
└─ .hqc

Patch
└─ Various bug-fixes
```

# Recent Deprecations / Breaking Changes

These are deprecations in the past 3 moderate versions (`x0.22.* -> x0.24.*`)

No Deprecations!

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
|                     | Generics                                                               | Done        |
|                     |     Classes                                                            | Done        |
|                     |     Structs                                                            | Done        |
|                     |     Unions                                                             | Done        |
|                     |     Functions & Methods                                                | Done        |
|                     | Variadic Generic Arguments                                             | Planned     |
|                     | Passable code blocks, eg `void example() code { code.eval() }`         | Planned     |
|                     | `restrict`, `out`, `inout`, `volatile`                                 | Done        |
|                     | Extern                                                                 | Done        |
|                     | Bitwise Logic                                                          | Done        |
|                     | Really fancy operator overloads                                        | Done        |
|                     | Try/Catch and `throw`                                                  | Done        |
|                     | Error message quality and helpfulness upgrade                          | Done        |

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
    `qout("True path");   // Executes!
} qelse {
    `qout("False path");  // ALSO executes!
}
```

---

---


## Manual Memory Management

```cpp
int main() {
    int* ptr = `malloc(sizeof "int");
    *ptr = 42;
    `qout("%p", ptr); 
    `free(ptr);
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

Based on the last reliable benchmark results, QuantumC showed performance in the same general range as C++, while offering a similar set of quality-of-life improvements found in languages such as Zig. Current benchmarks are being improved and results should be considered preliminary.

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
| **Protected Methods**                  | `__camelCase`          | Unique casing, more underscores.                                                                                             |
| **Private Methods**                    | `camel_Snake_Case`     | Function casing, more underscores.                                                                                           |
| **Namespaces**                         | `PascalCase`           | Same as user types.                                                                                                          |
| **Namespaces Not Meant For Inclusion** | `Pascal_Snake_Case`    | Unique casing style, more underscores, you have to be trying to include this.                                                |
| **Global Scope Functions**             | `camel_Snake_Case`     | Unique casing style, more underscores, similarity to private methods is intentional, because global scope cannot be included.|
| **Methods Used By Compiler**           | `_camelCase`           | Different from everything else. (these methods are iterators and stuff. Methods you define and compiler uses)                | 
| **Compiler Reserved**                  | `_qc_, __qc_ and qc_`  | Unique, hard to use accidently                                                                                               |
| **Compiler Intrinsics**                | \` + `snake_case`      | Unique, impossible to use accidently                                                                                         |

Max line size is around 120 _relative to your starting indentation_, tabs or spaces, lf newlines, comments are `//`, doc comments are `///`, and top-level doc comments are `//!`. File paths are unquoted, everything other than main should go in a namespace (not a strict rule, just a ideal, no need to follow), and namespaces should fit the following rules:

1. Namespaces should do one thing well, similar to the UNIX philosophy, 
2. Namespaces should have either:

        1. one type (or group of TIGHTLY related types, eg bigints) and their core helpers,
        2. above + namespaces containing extra helpers
        3. helper functions / utility functions (think a `Math` namespace with log, cos...)
        4. OR anything if directly mapping  C/C++/Zig/Rust code to C^4
3. Types in namespaces should have short names: The namespace should have the longer name
        e.g.
```qc
namespace Array {
    class Arr<T, int S = 0> {
        ...
    }
}
```
Pointer asterisks bind to the type rather than the variable. The final * belongs to the declarator, unless its a function return type. Then its all on the type.
```
int** *x;
int* ptr_add(int *p) ...
```
Files are `kebab-case` (optional, sometimes I dont follow this)
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
namespace Not_Embezzeling { // Intentionally formatted as a non-inclusion namespace.
    // Sure, you may not want to type all of that. That means your users absolutely don't.
    ..
}
```
## Ideals

QuantumC follows 4 core rules:

- Forced Cleanliness: QuantumC is designed to reward readable code. Language features should make the obvious solution the clean solution. Clean is not defined as 'Convenient for language', it means what it should be. Clean is not a "pythonic" equivalent, it is self-explanatory.
- Your Memory, Your Problem: QuantumC does not prevent dangerous code. It expects the programmer to understand the consequences. If you want, you can write a segfault handler with a segfault in it. QuantumC is strongly typed, but union types are designed to be ergonomic rather than restrictive. Unlike Rust or TypeScript, QuantumC does not force exhaustive narrowing before every union operation. I will give you a loaded shotgun. If you blow your leg off, don't blame the gunsmith.
- No Hiding: QuantumC is an explicit language: Your code does what it looks like it does. Nothing is hidden inside the parser yet pretends to be stdlib, nothing is hidden away in some back catacomb. If it is an intrinsic, it says it is.
- No Excessive Syntax: No capture lists on lambdas, no templates, no infinite <>, no Rust "bird droppings", no ! and @ everywhere.

## Compiler Architecture

QuantumC uses a classic multi-pass compilation pipeline:
1. **Lexical Analysis / Preprocessing:** Custom lexer converts text to tokens in one loop.
2. **AST Parsing:** Recursive descent parser generating a strongly typed Abstract Syntax Tree.
3. **Type Checking & Semantic Analysis:** Resolves user-defined types, namespaces, and TypeScript-style union types. The unique thing is that this pass is _merged with the compilation/codegen phase_
4. **Intermediate Representation (IR):** Generates LLVM IR. Target-aware pointer arithmetic is achieved dynamically via target-specific DataLayout queries.
5. **Codegen:** Emits native platform object files (`.o`) or WebAssembly binaries via LLVM's target machines.

---

## Multi Return

```cpp
int, string GetStatus() {
    return 200, "Success";
}
int main() {
    int code, string alias = GetStatus();
    `qout("%s", f"Code: {code}, AKA: {alias}\n");
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
)"/* your inline asm string */, "Hello, World", 14, "~{rax,rdi,rsi,rdx}" /* clobbers */);  
```
You can also use AT&T ASM syntax by making sure the first 5 characters of your ASM string are 
```asm
; ATT
```

## Storage & Argument Specifiers

QuantumC has 4 special (non-`const`) storage modifiers.

1. `volatile`
Volatile means the compiler won't optimize it. It can be used before variable declarations, or on function definitions. On methods, it must go after the access modifier and `final`, and before the return type.
```
volatile void infinite_time() {
    while(true) {
    }
    return;
}
```
2. `restrict`

`restrict` tells the compiler that this pointer is the exclusive access path to the referenced memory. Other unrelated pointers must not access the same memory in a way that violates the restrict contract. This allows more aggressive optimization.

Example:
```qc
void doSomePointer(int *restrict ptr, int *other) {
    *ptr = 10;
    *other = 20; // Undefined behavior if other points to the same memory as ptr
}
3. `out`
Out tells the compiler that this paramater is write-only, and this memory address will not be copied. It also only exists for optimization purposes.
```
void writeOnly(out int p) {
    p = 123; // OK
    int x = p; // ILLEGAL. Breaks contract.
    int *x = &p; // ILLEGAL also.
}
```
4. `inout`
Inout tells the compiler that this paramater will be read and wrote from but its address will not be copied.
```
void rw(inout int p) {
    p = 123; // OK
    int x = p; // OK
    int *x = &p; // NOT OK
}
```

## Variadic arguments

QuantumC variadic arguments look like this:
```cpp
int add_all(...args) {
    int res = 0;
    while (!`is_empty(args)) {
        res += `next(args, "int");
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
Generics are allowed on `struct`s, `class`es, unions, aliases, functions, and methods.
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
MyIterator<T> _map(fn(T elem) -> T) // preforms a operation on every element
MyClass<T> _collect() // returns the class that this iterator iterates
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
        this.current_index = `ternary(is_end, size, 0);
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
        this.data = `malloc(sizeof "T" * this.size);
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
    `qout("%i", my_vec[2]);
    return 0;
}
```

---
## Self Hosted Runtime
There is currently a unknown bug with the selfhosted runtime.

## Performance Comparison

Benchmarks are currently unreliable and show significant fluctuations between runs, or things like 0 millisecond runtime in O1 but 30 in O3. Results should be treated as preliminary rather than definitive. A more robust benchmarking system with better workload scaling and measurement methodology is planned after version x1.0.0.

## Known Limitations

&& and || do not shortcircut on unions.
Volatile does not exist on structs or class fields, and does not work on property accesses. In general, volatile is not 100%.

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
  Made by [Luca Fazio](https://github.com/Youg-Otricked)

