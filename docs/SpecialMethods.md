<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Special Methods

[Back to Home](./index.md)

### Special Methods:

|Name|Signature|Use|
|----|---------|---|
|`_repr`|`string _repr();`|Auto called as a string_representation, called when used in println, print, qout, fstrings|
|`_eval`|`bool _eval();`  |Auto called when you A: use a class in a if statement with no operators. B: when used on a operator that lacks a operator overload for that logical operator. Defaults to `bool _eval() { return true; }`|
|`operator?`|`type operator(opname)(single arg);`|Auto called when you use a logical or arithmetic operator on a class, eg `operator+` is called when you use `class + other thing`|

### Syntax And examples

```cpp
class Vector2 {
    int x;
    int y;
    Vector2(int x, int y) {
        this->x = x;
        this->y = y;
    }
    string _repr() {
        return f"X: {this->x}, Y: {this->y}";
    }
    bool _eval() {
        return true;
    }
    Vector2 operator+(Vector2 other) {
        Vector2 r = Vector2(0, 0);
        r.x = this->x + other.x;
        r.y = this->y + other.y;
        return r;
    }
    void operator=(Vector2 other) {
        this->x = other.x;
        this->y = other.y;
    }
}
int main() {
    
    Vector2 a;
    Vector2 b = Vector2(12, -33);
    a.x = 123;
    a.y = 321;
    `qout("%t", a);
    `qout(f"{a}, {b}");
    `qout("%t, %t\n", a, b);
    a += b;
}
```

##### **Important**: If using string concatenation you must manualy call the _repr method but only on normal + concat. Just use fstrings for this-> This is because if you do + concat it will try and call the .operator+ method instead of_repr.
