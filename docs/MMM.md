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
    qout("%i", x); // X is unchanged! Prints 21
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
    qout("%i", x); // X is edited by the pass-by-reference Prints 23
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