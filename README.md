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
|                     | Inline ASM                                                             | Done!!!     |
|                     | HTTP                                                                   | Coming Soon |
|                     | Generics                                                               | Coming Soon |
|                     | Passable code blocks, eg `void example() code { code.eval() }`         | Coming Soon |
|                     | Extern                                                                 | Coming Soon |
|                     | Bitwise Logic                                                          | Done!       |
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

## Preformance Comparison:
C^4 Code:
```cpp
int main() {
    long int sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i % 7;
        
        if (i % 2000000 == 0) {
            qout("%s\n", f"Checkpoint {i}, sum = {sum}");
        }
    }
    
    qout("%s", f"Final sum = {sum}");
    return 0;
}
```
C++ Code:
```cpp
#include <iostream>
int main() {
    long long sum = 0;
    for (int i = 0; i < 10000000; i++) {
        sum += i % 7;
        
        if (i % 2000000 == 0) {
            std::cout << "Checkpoint " << i << ", sum = " << sum << '\n';
        }
    }
    
    std::cout << "Final sum = " << sum;
    return 0;
}
```
C++ Compile time:
```bash
$ /usr/bin/time g++ ./qc/in.cpp
0.20 user 
0.01 system 
0:00.36 elapsed 
62% CPU (0 avgtext+0 avgdata 68024 maxresident)
0 inputs+32 outputs (0 major+6730 minor) pagefaults 0 swaps
```
C++ Runtime
```bash
$ /usr/bin/time ./a.out
Checkpoint 0, sum = 0
Checkpoint 2000000, sum = 5999997
Checkpoint 4000000, sum = 11999998
Checkpoint 6000000, sum = 18000003
Checkpoint 8000000, sum = 23999998
Final sum = 29999994
0.02 user 
0.00 system 
0:00.03 elapsed 
63% CPU (0 avgtext+0 avgdata 3656 maxresident)
0 inputs+0 outputs (0 major+147 minor) pagefaults 0 swaps
```
C^4 Compile time (silencing output to be more fair (becuase g++ does not print diagnostics or anything)):
```bash
$ /usr/bin/time qc ./qc/in.qc -c > /dev/null
0.16 user 
0.01 system 
0:00.31 elapsed 
57% CPU (0 avgtext+0 avgdata 70920 maxresident)
0 inputs+664 outputs (0 major+6374 minor) pagefaults 0 swaps
```
C^4 Runtime:
```bash
$ /usr/bin/time ./a.out
Checkpoint 0, sum = 0
Checkpoint 2000000, sum = 5999997
Checkpoint 4000000, sum = 11999998
Checkpoint 6000000, sum = 18000003
Checkpoint 8000000, sum = 23999998
Final sum = 29999994
0.02 user 
0.00 system 
0:00.03 elapsed 
55% CPU (0 avgtext+0 avgdata 1584 maxresident)
0 inputs+0 outputs (0 major+84 minor) pagefaults 0 swaps
```
### Comparing the results: (Note that C^4 has ZERO optimizations)
#### QuantumC Compile-time:
QuantumC used about 20% less CPU time (0.04 seconds faster at compiling in userspace).
QuantumC had 356 less minor pagefaults.
QuantumC was about 14% faster in wall clock time (0.31 vs 0.36)
#### QuantumC Runtime:
EXACT SAME RUNTIME SPEED AS C++.
QuantumC used roughly 57% less resident memory (used over 2000 less KB's of memory).
QuantumC had nearly half as many minor pagefaults.
In total: 
QuantumC:
consumes ~17% less CPU work overall.
was approximately 13% faster overall.
preformed identical to C++ during runtime.
achieved this result despite having zero optimization passes.

If compared to -O0 C++:
```bash
$ /usr/bin/time g++ ./qc/in.cpp -O0
0.20 user 
0.03 system 
0:00.33 elapsed 
70%CPU (0 avgtext+0 avgdata 66672 maxresident)
0 inputs+32 outputs (0 major+14106 minor) pagefaults 0 swaps
$ /usr/bin/time ./a.out
Checkpoint 0, sum = 0
Checkpoint 2000000, sum = 5999997
Checkpoint 4000000, sum = 11999998
Checkpoint 6000000, sum = 18000003
Checkpoint 8000000, sum = 23999998
Final sum = 29999994
0.02 user 
0.00 system 
0:00.04 elapsed 
52% CPU (0 avgtext+0 avgdata 3640 maxresident)
0 inputs+0 outputs (0 major+145 minor) pagefaults 0 swaps
```
Compared to -O0:
C^4:
During Compilation:
was 26% faster (0.06 seconds)
had over half as many minor pagefaults.
During Runtime:
used roughly 57% less resident memory (used over 2000 less KB's of memory).
had nearly half as many minor pagefaults.
Overall:
uses ~24% less CPU work.
was ~8% faster end-to-end.

## Known limitations:

- You cannot use + style string concat on class instances if you arn't entending the + to call the operator+ method because it won't call repr, instead it will try and call operator+ on the class with a string argument. This limitation doesn't exist on fstrings though.

## Ideals

QuantumC follows 4 core rules:

- Forced Cleanliness: Your code should and must be readable. Clean is not defined as 'Convinient for language', it means what it should be. Clean is not a "pythonic" equievalant, it is self explanitory.
- Your Memory, Your Problem: QuantumC does not stop you from doing somthing cool or implementing your dangerous ideas. QuantumC also doesn't stop you from making dangerous mistakes. Quantum C is strongly typed, but union types are designed to be ergonomic rather than restrictive. Unlike Rust or TypeScript, Quantum C does not force exhaustive narrowing before every union operation. I will give you a loaded shotgun. If you blow your leg off, don't blame the gunsmith.
- No Hiding: QuantumC is an explicit language: Your code does what it looks like it does. Nothing is hidden inside the parser yet pretends to be stdlib, nothing is hidden away in some back catacoamb. If it is a intrinsic, it says it is.
- No Excessive Syntax: No capture lists on lambdas, no templates, no infinite <>, no Rust "bird droppings", no ! and @ everywhere.
  Made by [Me](https://github.com/Youg-Otricked)
