<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Built-in Functions

[Back to Home](./index.md)

Quantum C has various built in functions, which are functions that are hard coded in the language, instead of you needing to manualy write them

|Function|Use|Signature|Example call|
|--------|---|---------|------------|
|`print`   |printing text to console. Text is not followed by a newline|`void print(string text);`|`print("Hello, World!\n");`|
|`println` |printing text to console. Text is automatically followed by a newline|`void println(string text);`|`println("Hello, World");`|
|`random`  |generating random numbers. If you pass no arguments, it returns a number from 0.00... (inclusive) to 1.00... (exclusive). If you pass a single integer argument, it returns a number from 0 (inclsive) to that number (exclusive). If you pass 2 integer arguments, it returns a number from number 1 (inclusive) to number 2 (exclusive)|`double random();` / `int random(int max);` / `int random(int min, int max);`|`random(123, 314);`|
|`seed`    |changes the currently used seed for random, to give different more random results|`void seed(int arg);`|`seed(1234);`|
|`time`    |returns the current timestamp as a integer. Mainly used to get a ever changing seed because otherwise random would always generate the same numbers.|`int time();`|`seed(time());`|
| `typeof`  | returns the data type of the value passed into the function | `string typeof(auto value);` | `int a = 0; println(typeof(a));` |
| `to_(type)` | there are several `to_?` functions, e.g. `to_bool`. They take compatible arguments and convert them to the target type. | `T to_T(auto value);` | `int n = to_int(true);` |
| `throw` |Making a error| `void throw(auto arg)`|`throw("Expected a name");`|
| `len`   |Returns the length of a string| `int len(string arg)` |`len("Hello, World!"); // 13`|
| `to_lower` |Returns a string in all lowercase| `string to_lower(string arg)` |`to_lower("Hello, WORLD"); // hello, world`|
| `to_upper` |Returns a string in all-caps     | `string to_upper(string arg)` |`to_upper("i spent 48 hours debugging namespaces"); // I SPENT 48 HOURS DEBUGGING NAMESPACES`|
| `substring` |Returns a part of a string | `string substring(string arg, int start, int stop)`|`substring("Hello, World", 0, 5);// Hello`|
| `split` |Returns a list of strings of a string split at a delimiter| `list<string> split(string arg, string delim)`|`split("Hello, World!", ","); // ["Hello", " World"]`|
| `join` |Returns a string that is a list of strings joined, and you pass a delimiter which is what the strings are joined with|`string join(list<string> splitstr, string delim)`|`join(split("a b c", " "), "-"); // a-b-c`|
| `contains` |Returns true if arg 1 contains arg 2|`bool contains(string arg1, string arg2)`|`contains("Hello, World", "Hello"); // true`|
| `startswith` |Returns true if arg 1 starts with arg 2|`bool startswith(string arg1, string arg2)`|`startswith("Hello, World", "Hello"); // true`|
| `endswith` |Returns true if arg 1 ends with arg 2|`bool endswith(string arg1, string arg2)`|`endswith("Hello, World", "Hello"); // false`|
| `trim` |Returns a string trimed of whitespace on both sides| `string trim(string arg)` |`trim("   this will be trimed   \n\t"); // this will be trimed`|
| `replace` |Returns a string with all occurences of arg2 replaced with arg3| `string replace(string arg1, string arg2, string arg3)` |`replace("this\nis\na\nstring", "\n", " "); // this is a string`|

