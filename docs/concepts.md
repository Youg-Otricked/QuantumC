<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

## Concepts
[Back To Home](./index.md)

Concepts serve two purposes:
- A `interface` equivelent
- Attaching behavior to structs without making them classes.

Unlike classes, structs remain plain old data (POD). Any methods introduced by a concept for a non-class usertype are compiled as ordinary functions that take an explicit Self parameter, unlike classes with a implicit this.

Declaring a concept
```qc
concept Printable {
    1_of {
        void print();
        void print(Self self);
    }

    default {
class:
        void print() {
            `qout("Printing...");
        }
else:
        void print(Self self) {
            `qout("Printing...");
        }
    }
}
```
## NUM_of
NUM_of (e.g. 1_of, 3_of) means that exactly NUM of the following constraints must be fullfiled

In the above example, any implementor with custom implementation must provide either a `void print()` or `void print(Self self)` method

## at_least
at_least is a modifier for NUM_of that just makes it at least instead of strict equality, eg `at_least 1_of`

## all_of
all_of means everything in this block must be provided

## Proving a concept

A type proves a concept using the `proves` keyword.
```qc
PDF proves Printable;
```

The compiler verifies that the type satisfies one of the required signatures. If an implementation is missing, the concept's default implementation is used if available, and otherwise errors.

## Providing additional definitions

Some types need custom implementations that aren't defined in the type itself, such as attaching behavior to structs
Use `with_proof` to provide them.
```qc
Paper proves Printable with_proof {
    void print(Self self) {
        `qout("%s", self.data);
    }
}
```
The contents of a `with_proof` block exist only for proving the concept.

## Self

Self refers to the implementing type.
For structs, concept methods always receive Self explicitly.
```qc
void print(Self self)
```
This keeps structs as plain data rather than giving them member functions.
Classes use ordinary member functions instead.

## Default implementations

Concepts may provide default implementations.
If a proving type does not implement a required operation, the compiler uses the default implementation when one exists.
Different defaults may be provided for classes and non-class types like this:
```qc
default {
class: 
    ...
else:
    ...
}
```

## Design Decisions
- Concepts cannot define operator overloads. This is to make it obvious that concepts are _not_ things to make everything classes. They are to provide _interfaces and implementation_
- Struct methods introduced through concepts always use an explicit Self parameter. This is to follow the `No Hiding` principle.

## Why explicit Self?
Structs in C^4 are intended to remain plain data containers. Concepts allow behavior to be associated with structs without turning them into classes. 
Requiring an explicit Self parameter makes this distinction visible in the language and avoids blurring the line between data and objects.

## Generics

You can use concepts as main constraints for generics.

```qc
concept Printable {
    ...
}
class Printer {
    void print<T(Printable:)>(T data) {
        data.print();
    }
}
```

## Bad Practices

Using `concept`s just to attach methods to a struct

```qc
struct MyStruct {
    ...
}
concept ThingForMyStruct {
    ...
}
MyStruct proves ThingForMyStruct;
```

