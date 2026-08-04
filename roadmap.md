- Concepts
```
concept Serializable {
    one_of {
        string serialize();
        string serialize(Self self);
    }
    default {
        string serialize() {
            return "No special implementation";
        }
    }
    all_of {...}
    at_least_one_of {
        ...
    }
    all_of {
        one_of {
            ...
        }
        all_of {
            ...
        }
    } // maybe
} 
class Y {
 ... 
} 
Y proves Serializable;
struct Z {
    ...
}
type T = int | string;
T proves Serializable;
Z proves Serializable with_proof {
    ...
} // provides bonus impl. Concepts are the only way to add methods to structs enums or unions and cannot have special methods / operator overloads.
```
- Variadic Generics (`class VaradicTypes<...Tys> { Tys elems; ...`) (not decided on syntax) 
- Code block functions (`void myKey() code { code.eval }; int main() { myKey () { …. } }`)
- Operator{} (code block in class, eg `<T> operator{}() code ()`, then `classinst { codeblock}`)
- Methos with code blocks
- Operator.
- Function pointers
- Friend (allows other classes to access)
- Private/Protected inheritance
- Static
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
modifier await type multivalue {
    use { // called when used
                … x = mod.values[...]
                …………..
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
- Void in () which means dont call with params or () and only for code block functions
```cpp
void loop(void) code {
    while (true) {
      code.eval();
    }
}
```
- Builtin Keyword, Identifier, and Type type that are basically just strings but let you type the raw token/ident/type
- Handlers for break continue and return in codeblocks
- Cqb lib in stl. Ci and build.
- qcheck (QC Lint(qc linter. duh)
- qconform (QC Formatter)
- `__attributes__((...))`
- const params/returns and const correct methods
- Copy VS Move assignment (no move only, im not rust), to make things faster.
- Scoping blocks ({ })
- more error stuff if i feel like it
__qc_commit_hash() — exact git commit the compiler/runtime was built from, invaluable for bug reports since version numbers alone often don't pin down exactly which state of the code produced a binary
__qc_build_date() — timestamp of the build
__qc_target_triple() — what platform/arch this runtime was compiled for (x86_64-linux-gnu, wasm32-unknown-unknown, etc.) — relevant since your lesson context here is literally about compiling toward WASM/LLVM targets
__qc_llvm_version() — since you're LLVM-backed, knowing which LLVM version built a given binary matters a lot for debugging codegen-level bugs that are version-specific
__qc_debug_build() — a bool baked in at compile time indicating whether this was a debug or release build, so runtime error handlers can decide whether to print verbose diagnostics or not
- atomics
- defer
TOP PRIORITY:
1. Static and Friend
2. Defer
3. Codeblocks.
4. Concepts
5. Modifier (x1.0.0)
6. Ident (maybe)/Type direct primitive type (parser refactor), make sizeof and next take a REAL TYPE! instead of a string
7. Variadics on generics
8. CQB (depends on codeblocks HEAVILY. same for trycatch. not to sure about the other tsuff though. ).
9. Other stuff + Variadic Generics
10. Metadata
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
11. Preproccessers
#define - define a constant value
#undef - undef a constant value
#if - if
#else - else 
#ifdef - if defined
#ifndef - if undefined
#endif - end if
#line - somthing idk
12. User-Defined metadata
13. User-Defined macro _functions_ (the only good thing in rust)
