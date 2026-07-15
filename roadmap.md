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
- -L (link) -A (alias)
- Generics (`class List<T, int S>`....., `class MultiNumbers<T(!int|double|float)>`, `class VaradicTypes<...Tys>`) everything but variadics done on classes, and need to do it for structs functions methods and unions
- Code block functions (`void myKey() code { code.eval }; int main() { myKey () { …. } }`)
- Operator{} (code block in class, eg `<T> operator{}() code ()`, then `classinst { codeblock}`)
- operator( )() (functor, can have codeblocks)
- Methos with code blocks
- Operator.
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
TOP PRIORITY:
1. Generics.
2. Self host the runtime.
3. Try/Catch.
4. Fancy operator overloads
5. Token/ident/type/keyword/usertype direct type (parser refactor)
6. Codeblocks.
7. Concepts
8. Modifier (x1.0.0)
9. CQB (depends on codeblocks HEAVILY. same for trycatch. not to sure about the other tsuff though. ).
10. Other stuff + Variadic Generics
11. Metadata
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
?references(ns, ns, ns)? - states which namespaces in this file this namespace references to say what to compile with it. (to increase compile speed. not sure if compile full file or nothing but that namespace if missing)
12. Preproccessers
#define - define a constant value
#undef - undef a constant value
#if - if
#else - else 
#ifdef - if defined
#ifndef - if undefined
#endif - end if
#line - somthing idk
