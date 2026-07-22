<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Inline Assembly

[Back to Home](./index.md)

QuantumC provides inline assembly similar to GCC's inline `asm`, but with a simplified syntax.

## Signature

```qc
void inline(string asm, ...args);
```

The first argument is an assembly string, for example:

```asm
R"(
mov rax, 1
mov rdi, 1
mov rsi, $0r
mov rdx, 13
syscall
)"
```

Operands are referenced using placeholders with the following syntax:

```
$<num>[=]<r|m|i|g>
```

Where:

- `num` is the operand number.
- `=` marks the operand as an output.
- `r` places the operand in a register.
- `m` places the operand in memory.
- `i` requires an immediate integer constant.
- `g` allows the compiler to choose the best location.

Output operands always come before input operands.

All arguments after the assembly string, except the final one, are operands referenced by the placeholders. The final argument is the clobber string, which tells the compiler which registers or resources are modified by the assembly.

The following clobber strings are equivalent:

```qc
"~{rax}~{rdi}~{rsi}~{rdx}~{memory}"
```

```qc
"~{rax,rdi,rsi,rdx,memory}"
```
