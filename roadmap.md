- Concepts
```
concept X {
...
} 
class Y {
 ... 
} 
Y proves X;
```
- Try/Catch 
- allow special character literals in generics, eg:
```
class Function<T, '(', V, ')'> {
    ...
}
...
Function<int(int)>;
```
- `-L (link)` and  `-A (alias)` flags
- Generics (`class List<T, int S>`....., `class MultiNumbers<T(!int|double|float)>`, `class VaradicTypes<...Tys>`) need to do it for functions and methods, and add variadic generics
- Code block functions (`void myKey() code { code.eval }; int main() { myKey () { …. } }`)
- Operator{} (code block in class, eg `<T> operator{}() code ()`, then `classinst { codeblock}`)
- operator( )() (functor, can have codeblocks)
- Methos with code blocks
- Operator.
- Function pointers
- Empty arrays with syntax `[int]`
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
- ~destructor
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
- operator++/–-/-/+=/-=//=/*=(combinational operators)
- operator<</|>\|>>/<<</&/......... (bitwise)
- const params/returns and const correct methods
- Copy VS Move assignment (no move only, im not rust), to make things faster.
- Actually decent error messages and errors (probbalt a lot of work)
- Scoping blocks ({ })
TOP PRIORITY:
1. Generics.
2. Volitile
3. Self host the runtime.
4. Try/Catch.
5. Fancy operator overloads
6. Token/ident/type/keyword/usertype direct type (parser refactor)
7. Empty arrays.
8. Codeblocks.
9. Concepts
10. Modifier (x1.0.0)
11. Variadics on generics
12. CQB (depends on codeblocks HEAVILY. same for trycatch. not to sure about the other tsuff though. ).
13. Other stuff + Variadic Generics
14. Metadata
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
15. Preproccessers
#define - define a constant value
#undef - undef a constant value
#if - if
#else - else 
#ifdef - if defined
#ifndef - if undefined
#endif - end if
#line - somthing idk
16. User-Defined metadata
