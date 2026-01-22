<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Built-in Functions

[Back to Home](./index.md)

Quantum C has various built in functions, which are functions that are hard coded in the language, instead of you needing to manualy write them

|Function|Use|Signature|Example call|
|--------|---|---------|------------|
|`print`   |printing text to console. Text is not followed by a newline|`void print(string text);|`print("Hello, World!\n");`|
|`println` |printing text to console. Text is automatically followed by a newline|`void println(string text);`|`println("Hello, World");`|
|`random`  |generating random numbers. If you pass no arguments, it returns a number from 0.00... (inclusive) to 1.00... (exclusive). If you pass a single integer argument, it returns a number from 0 (inclsive) to that number (exclusive). If you pass 2 integer arguments, it returns a number from number 1 (inclusive) to number 2 (exclusive)|`double or int random((optional)int arg1, int arg2);`|`random(123, 314);`|
|`seed`    |changes the currently used seed for random, to give different more random results|`void seed(int arg);`|`seed(1234);`|
|`time`    |returns the current timestamp as a integer. Mainly used to get a ever changing seed because otherwise random would always generate the same numbers.|`int time();`|`seed(time());`|
|`typeof`  |returns the data type of the variable passed into the function|`string typeof(string);`|`int a = 0; typeof("a");`|
|`to_(type)`|there are 7 different to_? functions, eg to_bool. They all take certain compatibal args and convert them to ? type and return them.|`? to_?(compatibletypes argument);`|`to_int(true);`|
