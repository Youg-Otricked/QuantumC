- Variadic Generics (`class VaradicTypes<...Tys> { Tys elems; ...`) (not decided on syntax) 
- Operator.
- Function pointers
- Private/Protected inheritance
- Modifier user type:
```cpp
modifier async type function {
    on_call {// called when func is called
        … x = mod.args[...];
        …………
    }
    on_return {
          … x = mod.return_values[...] // called on return
         ………………
    }
}
modifier await type value {
    use { // called when used
                … x = mod.value
                …………..
    }
}
```
Then you could do
```
async <func def> foo <rest of def>
…
await foo();
```
- float_bits and double_bits intrinsic (literal llvm `bitcast ` instruction)
- Fields to get all obj fields
- typeof(fn) giving a object with properties of argos ret types…  shape as a struct:
```c
typedef struct {
    char*[] return_types;
    char*[] arg_types;
    char*[] arg_names;
    char* name;
    char*[] modifiers;
    char*[] attributes;
    generic_constraint[] constraints;
} qc_function_typeof;
```
- Constexpr
- Debug
- Cqb lib in stl. Ci and build.
- qcheck (QC Lint(qc linter. duh)
- qconform (QC Formatter)
- `__attributes__((...))`
- const params/returns and const correct methods
- Copy VS Move assignment (no move only, im not rust), to make things faster.
- more error stuff if i feel like it
__qc_commit_hash() — exact git commit the compiler/runtime was built from, invaluable for bug reports since version numbers alone often don't pin down exactly which state of the code produced a binary
__qc_build_date() — timestamp of the build
__qc_target_triple() — what platform/arch this runtime was compiled for (x86_64-linux-gnu, wasm32-unknown-unknown, etc.) — relevant since your lesson context here is literally about compiling toward WASM/LLVM targets
__qc_llvm_version() — since you're LLVM-backed, knowing which LLVM version built a given binary matters a lot for debugging codegen-level bugs that are version-specific
__qc_debug_build() — a bool baked in at compile time indicating whether this was a debug or release build, so runtime error handlers can decide whether to print verbose diagnostics or not
- atomics
- destructuring (eg `Pair {abc, def} = ...`, operator{} which is your destructure handler (multi return baby!) (maybe))
- tuples (like zig/rust tuples, .0 .1 .2 .3)
- user defined literals (macros baby!)
- user defined macro functions
- user defined metadata tags
- Compile-time assertions (assert, static_assert)
- Decltype (get type of expr)
- noexcept (funciton modifier) (same update as const on functions and stuff)
- change parent constructor and delegeating constructors
- compile_error("My error")
- compile_log("My msg")
- dynamic field access
- has field, has method
- _generic- manal overloading
- rust like tags for enums
- 
        on_write
        on_read    on_type_decl
    on_member_access hooks for modifiers
TOP PRIORITY:
1. Expressions in concepts, kinda like C++, allong with allowing concepts on non-usertypes.
    concept Pointer {
        all_of {
            *ptr;
            ...
        }
    }
    int* proves Pointer, _ discard value
2. Modifiers, Atomics (x1.0)
2. Variadics on generics
3. Tuples + Destruturing
3. Function Pointers
3. Tagged enums
3. CQB
4. Other stuff (private/protected inheritance) + Variadic Generics, operator.
5. Metadata
?likely? - likely marked
?unlikely? - marked unlikely
?inline? - pls inline >-<
?inline(always)? - always inline
?inline(never)? -  NEVER inline
?nodiscard? - warn if discard result
?noreturn? - optimize away post-call cleanup
?deprecated(msg)? - warning with this message when used
?fully_deprecated(msg)? - ERROR with this message when used
?errordiscard? - nodiscard but errors not warns
?consteval? - evaluate at compile time
?qc_ver_eq(version)? - errors if qc ver is != version
?qc_ver_lt(version)? - errors if qc ver is >= version
?qc_ver_gt(version)? - errors if qc ver is <= version
?qc_ver_lte(version)? - errors if qc ver is > version
?qc_ver_gte(version)? - errors if qc ver is < version
?since(ver)? - states the version of the package this is for
?until(ver)? - states when this will be deprecated
?experimental? - states that this tool is janky, subject to change, or flaky/expremintal
?unstable? - states this tool is janky, flaky, or unstable, but api won't change
?sentinel(value, msg, value, msg....)? - states this tool returns sentinel values with special meaning
6. Preproccessers
#define - define a constant value
#undef - undef a constant value
#if - if
#else - else 
#ifdef - if defined
#ifndef - if undefined
#endif - end if
#line - somthing idk
7. User-Defined metadata
8. User-Defined macro _functions_ (the only good thing in rust)
9. User defined literals
10. co_await
