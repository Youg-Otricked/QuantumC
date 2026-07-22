<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Manual Memory Managment

[Back to Home](./index.md)

Their are a few important concepts to manual memory managment:

## References

References can be thought of as aliases of a variable. _You can only make references to variables_.
Refs arn't very useful when just creating a reference to a variable, but what makes them useful is when passing them to functions.

Functions are normally _pass by value_. This means that when you pass a variable to a function, you are passing the value of it instead, e.g:
```cpp
void add(int a, int b) {
    a += b;
}
int main() {
    int x = 21;
    add(x, 2); // Passes a copy of x and 2 to the function
    `qout("%i", x); // X is unchanged! Prints 21
}
> 21
```

Meanwhile, references allow you to pass the _actual memory address (later) of the variable! (pass-by-reference)
```cpp
void add(int& a, int b) {
    a += b;
}
int main() {
    int x = 21;
    add(x, 2); // Passes the actual variable x and 2 to the function
    `qout("%i", x); // X is edited by the pass-by-reference Prints 23
}
> 23
```

To declare a reference, you put & after the type.
```cpp
int& x ...
```
References _must_ be intialized on declaration.
```cpp
int& rx; // ERROR: References must be intialized.
// VS
int x = 0;
int& rx = x; // OK
```
The same logic applies to function parameters.
However, you shouldn't use references in function _returns_. This is because in programs, their are 2 areas: The Stack, and The Heap. The stack is a place that is automatically allocated when you create a variable. It could look somthing like this
```cpp
// stack = 0x1()0x2()0x3()0x4()0x5()0x6()...
int x = 0; // allocates space on stack for 0. Let's say address 0x4.
// stack = 0x1()0x2()0x3()0x4(0x0)...
```
However, the stack has somthing called _frames_. Whenever a function is called, a new stack frame is pushed(created), and whenever a function returns, it is "popped" off (deleted). This is why you can't access vars from other functions.
```cpp
int add2(int z) {
    return z + 2; // FRAME POPPED! stack = frame1(0x1(0x0)0x2()...)
}
int main() {
    // assuming stack allocates one address after the other (not realistic)
    int x = 0; //stack = frame1(0x1(0x0)0x2()...)
    add2(x); // FRAME PUSHED! stack = frame1(0x1(0x0)0x2()...) frame2(0x1(0x0)0x2()...)
    z++; // INVALID: z no longer exists.
}
```
So, if you create a reference to a variable in a function and return it, the reference has the address of memory that doesn't even exist.
```cpp
int& get2() {
    int x = 2;
    return x;
}
int main() {
    int x = get2(); // x stores somthing that doesn't exist. This is either undefined behavior or a "segfault" (basically you did somthing illegal with memory.)
}
```
## Addresses

All data in a program is stored in memory.
Memory is a large region of addressable storage. Each location in memory has an address that can be used to access it.
A memory address is a number (usually shown in hexadecimal) that identifies a specific location in memory.
You can think of memory addresses as being analogous to real-world addresses. They are similar in the sense that both identify locations, but memory addresses refer to positions in a linear storage space.
For example, a delivery driver uses a house address to find where to drop off a package. In a program, the cpu looks at the memory address to find the value.

## Pointers

Pointers just store a address. Simple! Or is it?... *queue vsauce intro*
_Stack_ pointers are simple at the top level:
```cpp
int x = 123;
int* p = &x; // & is the address of operator, and gets a pointer to the address of that variable
```
You can dereference pointers to get their value
```cpp
`qout("%i", *p); // 123
```
However, you can also do addition, subtraction, and indicing on pointers!
Arrays can be _decayed_ to pointers, which means they lose there length becomes unknown, but can be used as a pointer. To make an array a pointer, you can take the address of the first element.
```cpp
int x = 10;
int y = 20;
int z = 30;
int* p = &x;
int* p2 = p - 1; 
p2[0] = 99;
```
Most of the time arrays do array automaticaly though.
In this example, it is dangerous because p is a _stack_ pointer. P points to x, and their is a liklyhood that x y and z are near eachother so that area of the stack is initialized.
The line `int* p2 = p - 1;` subtracts 4 bytes from the position of p (becuase int is 4 bytes), and store it at p2. p2[0] is the equivelent of *p2, and p2[1] is equivelant to *(p2 + 4)

## How does one store an address?

Sometimes we have an address as a number. We can store it with the `addr_t` type.
```qc
addr_t x = 0xdeadbeefDEADBEEF
```

Allowed number formats:

Octal
```
0o76543210
```
Hex
```
Oxfedcba9876543210
```
Binary
```
0b10
```
Decimal
```
9876543210a // must end in a, just like how long must end in l and short must end in s and float must end in f
```

## Converting Pointers To Addresses (and vis-verca)

QuantumC has simple helpers for that.
```
long int y = 9l;
long int* x = &y;
addr_t ptr_addr = `to_address(x);
long int* ptr_from_addr = `mapped_ptr(addr_t);
```

## The Heap

While the stack is cool and allows us to have easy pointers we all need the heap.
The heap is just like C in QuantumC.
```
void* `malloc(addr_t sizeInBytes)
```
The full cstdlib mem group (realloc calloc free) is also available.

To get the size of a type in bytes, you use the `sizeof` helper.

```
sizeof "int"; // a stringified type, returns 4 (size of the "int" type)
int x = 0;
sizeof x; // a non-constant non-string, returns 4 (the size of x's type)
int* p = `malloc(sizeof "int");
*p = 42;

`free(p);
p = nullptr; // recommended
```

`nullptr` is the null pointer. Internally it has the address value 0, but it does not point to valid memory. Its what you assign to invalid pointers.

## Stack VS Heap

| Stack               | Heap               |
| ------------------- | ------------------ |
| Automatic           | Manual             |
| Fast                | Slower             |
| Freed automatically | Lives until `free` |


## Refs VS Ptrs

| References            | Pointers                    |
| --------------------- | --------------------------- |
| Must be initialized	| Can be null                 |
| Cannot be reseated	| Can point elsewhere         |
| No Pointer Arithmetic | Pointer Arithmetic allowed  |
| Implicit dereference  | Explicit *                  |

## Why heap?

Dangling Pointers.

Dangling Pointers are when you return a pointer that is no longer pointing to a valid value.
```qc
int *addPtr(int a, int b) {
    int res = a + b;
    int *resP = &res;
    return resP; // Dangling pointer: res is deleted when the function exits and the stack pops.
}
int main() {
    int *x = addPtr(1, 3);
    *x;
    // Undefined behavior.
    // Often crashes with a segmentation fault.
}
```

Freeing when you don't know if you should free it / it has already been freed is also dangerous
```qc
int *x = `malloc(sizeof "X");
`free(x);
`free(x); // UB / SIGSEGV Segmentation Fault (Core Dumped)
```

However not freeing causes somthing called "leaked memory" which means that the memory is never freed and cannot be used because it has been allocated and cannot/has not been freed.
```qc
void doSmnth() {
    int *x = `malloc (sizeof "X");
    ...
    return; // MEMORY LEAK. X was allocated and never freed and now the program has lost that memory.
}
```

Because of this, classes should have a `_destroy` method, which `free`s all heap-allocated memory of the class. Note that `_destory` is _not_ responsible for cleaning up heap-objects _you_ create in that class. 
Eg if we have a generic class:
```qc
class C<T> {
    T *data;
    C() {
        this.data = `malloc(sizeof "T");
    }
    void _destroy() {
        `free(this.data);
    }
}
int main() {
    C<int*> x = C();
    x.data = `malloc(sizeof "int");
    x._destroy(); // MEMORY LEAK and not C's fault. C only knows it owns the storage for T. It has no idea that T itself is another pointer requiring cleanup.
    // You should do:
    // `free(*x.data);
    // x._destroy();
}
```
Ownership (who should free) is simple.
Ownership Rules:
- If you allocate it, you free it.
- If you return it, the caller frees it.
- If your class owns it, free it in `_destory`.
- If your class merely stores someone else's pointer, don't free it.
