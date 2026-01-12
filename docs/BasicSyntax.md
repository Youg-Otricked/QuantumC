<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Basic Syntax

[Back to Home](./index.md)

### Math

**Note that ?= means any number of quesiton marks charecter logic operator equals so ?= means += or -=...**
In QC there are various binary math operators. Examples are:


|Operator|Usage |Effect        |
|--------|------|--------------|
|'+'     |L + R |Addition      |
|'-'     |L - R |Subtraction   |
|'*'     |L * R |Multiplication|
|'/'     |L / R |Division      |
|'**'    |L ** R|Power         |
|'%'     |L % R |Modulo        |
|'?='    |L ?= R|Combinational |

##### Effects:
- +: Addition: 5 + 2 = 7;
- -: Subtraction: 5 - 2 = 3;
- *: Multiplication: 5 * 2 = 10;
- /: Division: 5 / 2 = 2.5;
- **: Power: 5 \*\* 2 = 25;
- %: Modulo: 5 % 2 = 1;
- ?=: Combinational expresion. a ?= x is equal to a = a ? x;

Modulo returns the remainder of a division.

---

### Boiler Plate

Function syntax will be coverd later, but the boilerplate for Quantum C is simple.
```cpp
int main() {
    // Code Goes Here
}
```
No includes, no nothing.

### Variables
Variables in Quantum C are declared as follows:
```cpp 
type name = value;
// OR
type name;
```
The datatypes are string, char, int, float, double, bool, and qbool, with the modifiers const, long, and short. Example:
```cpp
int main() {
    string StringEx = "This is a string"; // Strings are a list of characters
    char CharExNewline = '\n'; // Chard are a single charecter, 4 digit unicode, or escape sequence
    bool BoolEx = true; // Booleans are true or false
    qbool QboolEx = both; // QBools are qtrue qfalse both or none
    int Num = 123456789; // ints are any 32 bit whole number (any number between -2147483648 and 2147483647)
    float FloatPi = 3.141592f; // floats are a 32 bit floating point number (7 digits of persision.)
    double DoublePi = 3.141592653589793; // doubles are 64 bit floating point numbers (14 digits of persision.)
    // MODIFIERS
    const double Pi = 3.141592653; // Const means that a variables value cannot be changed
    long int LINT = 9223372036854775807; // Long can be used on double and int and doubles the numbers size
    short int SHINT = 32767; // Short affects int and halfs its size
}
```

# Console Output

The main way to output to console in Quantum C is std::qout ((<< text or variable or escapesequence)can repeat);, eg std::qout << "Hello, World" << '\n';