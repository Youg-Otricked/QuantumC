<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Changelog
[Back to home](./index.md)

1/7/2026: Current version: 3.3: Adding docs.
1/7-13/2026: Current version: 4.5-4.7: Structs, Unions, Typedef.
1/13/2026: Current version: 5.0: Enums
1/15/2026: Current version: 5.2->8: Classes, other stuff
NAMESPCACES!!!!!!!!!!
1/27/26: Current version: 10.0.0(i missed a lot of changelogs). Multifile, more stdlib, typing, trycatch
1/28/26: Changed power operator from ** to ^*
5/6/26: I haven't updated this change log in FOREVER. Refactord IO to make pointers in compielr easier. Input is now `qin` instead of `std::qin`, and instead of ouptut using C++ style << and being called `std::qout`, it is called `qout`, and uses the C-style formater.
6/3/26: I still havent made good on updating this. Welp, i changed power for hopefully the final time-now it is #^
# Features checklist (suitable for change(by adding more))

- Interpreter
    - [x] User Types (
        - [x] Structs
          - [ ] Generics
        - [x] Enums
        - [x] Unions
        - [x] Classes
          - [ ] Generics
        - [x] ~~Template~~ (Replaced by Unions)
        - [x] Typedef
        - [x] Namespace
        - [ ] Modifier
    )
    - [x] Manual Memory Managment (
        - [x] Pointers (\*)
        - [x] Address syntax (&)
        - [x] Malloc
        - [x] Free
        - [x] Realloc
        - [x] Calloc
        - [x] ->
        - [x] Deref
    )
- Compiler
    - [x] User Types (
        - [x] Structs
          - [ ] Generics
        - [x] Enums
        - [x] Unions
        - [x] Classes
          - [ ] Generics
        - [x] ~~Template~~ (Replaced by Unions)
        - [x] Typedef
        - [x] Namespace
        - [ ] Modifier
    )
    - [x] Manual Memory Managment (
        - [x] Pointers (\*)
        - [x] Address syntax (&)
        - [x] Malloc
        - [x] Free
        - [x] Realloc
        - [x] Calloc
        - [x] ->
        - [x] Deref
    )
- [x] Including other files (
    - [x] Include via namespace with syntax #include \<namespacename, path-to-file>
)
- [ ] Standard library (
    - [x] Advanced random quantum booleans
    - [x] Math
    - [x] Collections
    - [x] Utils
    - [x] UnitTest
    - [ ] Ever growing
)
