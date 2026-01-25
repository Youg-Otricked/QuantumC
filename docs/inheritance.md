<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Inheritance

[Back to Home](./index.md)

## What is inheritance?

Inheritance lets one class **reuse and extend** another class.

- The original class is the **base class** (or **parent**).
- The new class is the **derived class** (or **child**).
- The child gets all the fields and methods of the parent, and can add more or override some.

In Quantum C you write:

```cpp
class Base {
    int x;
    Base(int x) {
        this.x = x;
    }
    void say_x() {
        println(f"Base x = {x}");
    }
}

class Child : Base {
    int y;
    void say_xy() {
        println(f"x = {this.x}, y = {this.y}");
    }
}
```
Here, `Child` inherits from `Base`:

`Child` has `x` and `say_x()` from `Base`,
Plus its own `y` and `say_xy()`.
Basic syntax
```cpp
class Parent {
    // fields
    // methods
}

class Child : Parent {
    // extra fields
    // extra methods
}
```
You can then use it like:
```cpp
int main() {
    Child c;
    c.x = 10;        // from Parent
    c.y = 20;        // from Child
    c.say_x();       // method from Parent
    c.say_xy();      // method from Child
    return 0;
}
```
Constructors and init with inheritance
If the base class has a constructor, the child can call it inside its own constructor (using your normal method call rules). If there is no constructor, init() on the parent/child is used for default initialization when you declare a variable without =.

Very roughly:
```cpp
class Base {
    int x;
    Base(int x) {
        this.x = x;
    }
    void init() {
        x = 0;
    }
}

class Child : Base {
    int y;
    Child(int y, int x) {
        Base(x);
        this.y = y;
    }
    void init() {
        Base(constructorargs)// Calls init or zero initlizes if you don't call constructor in constructor
        y = 0;
    }
}
```

Overriding methods
A child can define a method with the same name as the parent’s method to “override” it:
```cpp
class Animal {
    void speak() {
        println("Some animal noise");
    }
}

class Dog : Animal {
    void speak() {
        println("Woof!");
    }
}

int main() {
    Dog d;
    d.speak(); // prints "Woof!"
    return 0;
}
```
The child’s speak() replaces the parent’s speak() when called on a Dog instance.

## Why use inheritance?

- Reuse: put common fields and methods in a base class.
- Extend: add extra behavior in derived classes.
- Organize: model “is a” relationships (e.g. Dog : Animal, Player : Entity).

Use inheritance when one thing really is a kind of another thing, and you want to share code between them.

3 more inheritance features are A: abstract classes, B: final, and C: **_Protected_**

Abstract classes are the exact same thing as classes but you put abstract before class, and you cannot create instances of them, only make children of them.
```cpp
abstract class Base {
    int x;
    int y;
}
class Point : Base { ...} // OK

int main() {
    Base thing; // NOT OK
}
```

Final means somthing can no longer be inherited from.

```cpp
class Thing {
    final public string get_name() {
        return "This is a name";
    } // This method cannot be overwriten in child classes.
}
```

and protected is simple.
**Protected** means the field/method can be accessed by:
- The class itself
- Any child class
- Any grandchild class (and so on...)
- NOT by outside code (like `main()`)

```cpp
class Base {
    protected int shared_value;
    
    Base(int val) {
        this.shared_value = val;
    }
}

class Child : Base {
    void modify() {
        this.shared_value = 100;
    }
}

class GrandChild : Child {
    void change() {
        this.shared_value = 200;
    }
}

int main() {
    GrandChild g;
    // g.shared_value = 50;  // ERROR: protected!
    return 0;
}
```
Use protected when:

- You want child classes to access something
- But you don't want outside code to touch it

