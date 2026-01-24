<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# OOP

[Back to Home](./index.md)


# Classes

Classes are _very_ similar to structs, but they have a few core differences. Classes have something called **methods**, and access modifiers. Methods are functions in the class.

You make a class with this syntax:
```cpp
class class-name {
    field-type field-name...;
    function definition...;
}
```

Another core part of classes are somthing called _constructors_. Constructors are things that you call to initilize a class. You make a constructor by making a function, with **_no return type_** and the name is the name of the class. You access fields inside the class with "this.". An full example class would be:
```cpp
class Vector2D {
    int x_pos;
    int y_pos;
    Vector2D(int x, int y) {
        this.x_pos = x;
        this.y_pos = y;
    }
    int[] get_pos() {
        return [this.x_pos, this.y_pos];
    }
}
```

To make a member of this class you would do:

```cpp
Vector2D vector = Vector2D(2, 123);
```
You, of course could call the Vector2D function with any arguments.

Now, time to get to access specifiers, and what they are for, which is somthing called _**Encapsulation**_.

Encapsulation is when you hide eveything that the user doesn't need.

In Quantum C, you do that with somthing called _Access Specifiers_.
The 2 most common access specifiers are **_public_ and _private_**
public means it can be accessed **by any class member and any class and any code** but private means **only this class can access it**
```cpp
class PrivateAndPublic {
    private int private_field;
    public string public_field;

    PrivateAndPublic(int a, string b) {
        this.private_field = a;
        this.public_field = b;
    }

    private void private_changer() {
        this.private_field += 1;
    }

    public void thing() {
        this.private_changer();
        this.public_field = "thing";
    }
}
int main() {
    PrivateAndPublic thingy = PrivateAndPublic(123, "THING");
    // println(thingy.private_field); <- this would error
    // thingy.private_changer(); <- this would also error
    println(thingy.public_field); // OK
    thingy.thing(); // Also OK.
}
```