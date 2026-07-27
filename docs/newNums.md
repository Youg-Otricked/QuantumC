<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

## New Numbers
[Back To Home](./index.md)

Short page.

QuantumC exposes _every_ integer bitwidth from 1 to 64 (or 1 to 32 if your running a 32 bit system) as a primitive type.
```
bool = u1
qbool = u2
nibble = u4
byte = u8
char = i8
short int = i16
int = i32
long int = i(pointersize)
addr_t = u(pointersize)
```
