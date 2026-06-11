- Array-initing pointers
- Link multiple qc files by compile then compile then link. basically just compile all files with oo then `clang <file .o s>`
- Try/Catch 
- Polymorphic pointers. Class* = &Child
- Generics (`class List<T, int S>`....., `class MultiNumbers<T(!int|double|float)>`, `class VaradicTypes<...Tys>`)
- Operator[i] (subscript, eg `class[123]`), operator[](brace initialization, eg `Classname c = [1, 2, 3, 4]`), operator{:}(map initialization, e.g. `Classname c = {"true": 1, "false": 0};`)
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
- Special "call" function that calls a function based off of a string
```cpp
call("foo");
```
- Fields to get all obj fields
- typeof(fn) giving a object with properties of argos ret types…  shape as a struct:
```c
typedef struct {
    char*[] return_types;
    char*[] arg_types;
    char*[] arg_names;
    char* name;
} qc_function_typeof;
```
- Constexpr
- Debug
- ~destructor
- … varadics
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
- operator++/–/+=/-=//=/*=(combinational operators)

TOP PRIORITY:
1. Refactor include system to allow referencing internal code instead of full directo copy pase. Also nested namespace and multi include one line. Also full dir scans, synatx like `#include<llvm::Types, llvm::Values, "~/llvm/src/">`.
2. Array-initing pointers.
3. CLI Args, Link multiple files, simple stuff.
4. Polymorphic pointers.
5. Generics.
6. Try/Catch.
7. Fancy operator overloads
8. Token/ident/type/keyword/usertype direct type (parser refactor)
9. Codeblocks.
10. CQB.