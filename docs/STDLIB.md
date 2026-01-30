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
