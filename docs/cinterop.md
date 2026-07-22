<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

## C Interop

[Back to home](./index.md)

QuantumC uses the C ABI for external interoperability.

There are two directions:

## 1. Export QuantumC code

To expose QuantumC functions to other languages through the C ABI:

```qc
extern:
int add(int a, int b) {
    return a + b;
}
:extern
```
This is equivelant to 
```c
extern "C" {
}
```
in many other languages.

## 2. Import external functions

To use functions provided by an external C ABI-compatible library or file:

```
foreign:
int add(int a, int b);
:foreign
```

This is like puting signatures in a `extern "C"` in other languages.
