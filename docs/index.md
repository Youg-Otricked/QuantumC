<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">


# Welcome To The Quantum-C Documentation!

```cpp
int main() {
    qbool state = both;
    qif (state) {
        std::qout << "Quantum!" << '\n';
    }
}
```

### Pages:
[Features](./desc.md)
[Getting started](./getStart.md)
[Changelog/Features-checklist](./change.md)
[Basics](./BasicSyntax.md)
[Collection types](./CollectionTypes.md)


## 'Philosophy'

- No hidden behavior
- No implicit magic (auto is highly discouraged)
- Errors should be as loud and early as possible, not console filling variant messes
- If something is complex, it is documented as complex

Quantum C favors clarity over convenience, and explicitness over brevity.

## Non-goals

- Quantum C is not trying to do 'hand-holding' or be beginner - friendly.  
  It is designed to be **used**, **taught**, and **to teach** — and this can be **verified directly**:  
  simply pass `-a -tkn -r` before any input file to see the compiler output that demonstrates all three.

- Quantum C does not hide memory costs
- Quantum C does not auto-correct ambiguous logic
- Quantum C does not _make_ ambiguous logic
- Quantum C does not _allow_ ambiguous logic

## Versioning

Quantum C uses feature-based versioning during early development.

- Minor version increments indicate new language features
- Patch versions are used for bug fixes and documentation changes
- Breaking changes may occur at any version below 2.X
