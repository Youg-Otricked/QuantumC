<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Quantum Control Flow

[Back to Home](./index.md)

### Control flow keywords

|////|Use|Syntax|Pro/Con|
|----|---|------|-------|
|**qif**|The basic (q)control flow|qif (condition) { code }|The easiest to understand|
|**qelse**|Add fallback/DNF for qif|qifblock {} qelse { code }|More power for qif|
|**qelif**|add another condition for qif. Equivelent to qelse { qif () {}}|qif block {} qelif (condition) {}|More conditions for qif|
|**qswitch**|Allows for checking the both or none values|qswitch (variable) {case t: code; break;.....}|Bit clunky, very usefull|

### Syntax And examples

```cpp
int main() {
    qbool flag = both;
    qif (flag) {
        println("Flag is true");
    } qelse {
        println("Flag is false");
    }
}
```
In the above code, it would print both, as flag is true AND false

qswitch syntax is as follows:
```cpp
qswitch (qboolval) {
    case t: // Runs if qtrue
        code;
        break;
    case f: // Runs if qfalse
        code;
        break;
    case b: // Runs if both
        code;
        break;
    case n: // Runs if none
        code;
        break;
}
```