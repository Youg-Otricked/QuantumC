<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Control Flow

[Back to Home](./index.md)

### Control flow keywords

|////|Use|Syntax|Pro/Con|
|----|---|------|-------|
|**if**|The basic control flow|if (condition) { code }|The easiest to understand|
|**else**|Add fallback/DNF for if|ifblock {} else { code }|More power for if|
|**else if**|add another condition for if. Equivelent to else { if () {}}|if block {} else if (condition) {}|More conditions for if|
|**switch**|Equivelent to if else if else if.....|switch (variable) {case value: code; break;.....}|Bit clunky, very small|

### Logical Operators

Operators are symbols you use on booleans (or non booleans) to evaluate expressions, for example if (true) runs. if blocks run if the condition is true nad the condition is a logical expression

|Operator|Name|Syntax|Use|
|--------|----|------|---|
|&&      |AND |L && R|If both sides are true, then it evaluates to true|
|\|\|    |OR  |L \|\| R|If either side is true, it evaluates to true|
|!       |NOT |!L    |Evaluates to the opisite of argument(L)|
|&zwj;^  |XOR |L ^ R |If left is true and right is false or right is true and left is false, evaluates to true|
|&zwj;>  |Greater than|L > R|If the left number is more than the right number, true|
|<       |Less than|L < R|If the left number is less than the right number, true|
|>=       |Greater than or equal to|L >= R|If the left number is more than or equal to the right number, true|
|<=       |Less than or equal to|L >= R|If the left number is less than or equal to the right number, true|
|==       |Is Equal|L == R|If the left value is the same as the right value, true|
|!=     |Not Equal To|L != R|If the left value is not the right value, true|

### Syntax And examples

```cpp
int main() {
    bool flag = true;
    if (flag) { // This block will run
        std::qout << "This will run if flag is true" << '\n';
    } else { // This won't
        std::qout << "This block would have ran if the block above didn't run" << '\n';
    }
    bool other = false;
    if (!flag) { // This block won't run because the opisite of true is false
        std::qout << "This block won't run" << '\n';
    } else if (flag && other) {// This block won't run because true and false is false
        std::qout << "This block also won't run" << '\n';
    } else { // This block runs;
        other = true;
        if (flag ^ other) {// This block won't run because other and flag are both true
            std::qout << "This block won't run" << '\n';
        } else if (flag || other) { // This block runs because at least one side is true
            std::qout << "This block runs" << '\n';
        }
    }
}
```

Switch syntax is as follows:
```cpp
switch (variable) {
    case possiblevalue:
        code;
        break;
    case...
    default:
        //this code runs if no cases matched.
}
```
Why the break is after the code is because somthing called fallthrough:
```cpp
int num = 1;
switch(num) {
    case 1:
        std::qout << "The variable is 1" << '\n';
    case 2:
        std::qout << "The variable is 2" << '\n';
}
```
In the code above, the output would be:
```
The variable is 1
The variable is 2
```
That is because switches fall through to the next case if a break is missing. This is usefull for things like this.
```cpp
switch (thing) {
    case allowedstate1:
    case allowedstate2:
    ...
        dosomthing
        break;// All allowed state 1, allowedstate2... all do the same thing and you don't need to repeate
    default:
        break;
}
```
