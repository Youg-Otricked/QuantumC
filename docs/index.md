<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">


# Welcome To The Quantum-C Documentation!

```cpp
int main() {
    qbool state = both;
    qif (state) {
        qout("Quantum!\n");
    }
}
```

## Video

<div style="position: relative; padding-bottom: calc(51.0933% + 41px); height: 0; width: 100%; max-width: 900px; margin: 0 auto;">
  <iframe
    src="https://demo.arcade.software/YKKoQ8dvslZT7VIXJVgH?embed&embed_mobile=tab&embed_desktop=inline&show_copy_link=true"
    title="Run and Test C Code in Quantum C Playground"
    frameborder="0"
    loading="lazy"
    webkitallowfullscreen
    mozallowfullscreen
    allowfullscreen
    allow="clipboard-write"
    style="position: absolute; top: 0; left: 0; width: 100%; height: 100%; color-scheme: light;"
  ></iframe>
</div>

## NOTE:
# **THIS IS NOT A QCL (Quantum Computation Language)**

### Pages:
[Features](./desc.md)

[Getting started](./getStart.md)

[Changelog/Features-checklist](./change.md)

[Basics](./BasicSyntax.md)

[Collection types](./CollectionTypes.md)

[Control flow](./ControlFlow.md)

[Loops](./Loops.md)

[Functions](./Functions.md)

[Builtins](./BuiltInFunctions.md)

[Advanced function features](./AdvancedFunc.md)

[QBools](./QBools.md)

[Q Control Flow](./QFlow.md)

[User Types](./UserTypes.md)

[OOP](./OOP.md)

[Special Methods](./SpecialMethods.md)

[Inheritance](./inheritance.md)

[Namespaces](./namespaces.md)

[Multi File](./include.md)


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
`
## Versioning

Quantum C  uses a feature-based versioning scheme.

- Minor versions indicate new language features
- Patch versions indicate bug fixes and documentation changes

### Legacy Versions

All legacy `v*` versions are deprecated. This includes the old release line up to `v12.0.0`.

### Current Versions

The current release line starts at `x0.15.0`.

Current `x*` versions are the non-deprecated versions going forward. For example, `x1.0.0` is part of the current version line and is distinct from the old legacy `v1.0.0`.`