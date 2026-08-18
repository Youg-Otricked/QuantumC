<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Iterators

[Back to Home](./index.md)

QuantumC's iterator system is designed to be simple to implement while providing a consistent interface for users.

Iterators work as follows:

A type is iterable if it defines the following method:

```qc
MyIterator _begin() // Returns a iterator to the begining of the class
```
`_end` is optional, and returns a iterator to the end of the class.
The iterator itself is required to define the following 2 methods:
```qc
bool _atEnd() // Returns true if there is nothing left to iterate
T _next() // Returns the current value then moves to the next
```
and may define the following recommended extra methods:
```qc
bool _atStart() // Returns true if the itertor is currently at index 0
T _prev() // Returns the element at current index -- and decrements current index
void _moveTo(whateveryouwant idx) // sets index to idx
MyIterator<T> _map(fn(T elem) -> T) // preforms a operation on every element
MyClass<T> _collect() // returns the class that this iterator iterates
```

Example:
```qc
class ArrayIterator<T> {
    T* data;
    int size;
    int current_index;
    ArrayIterator(T* data, int size, bool is_end) {
        this->data = data;
        this->size = size;
        this->current_index = `ternary(is_end, size, 0);
    }
    bool _atEnd() {
        return this->size <= this->current_index;
    }
    T _next() {
        if (!this->_atEnd()) {
            return this->data[this->current_index++];
        }
        return this->data[this->current_index];
    } 
    bool _atStart() {
        return this->current_index <= 0;
    }
    T _prev() {
        if (!this->_atStart()) {
            return this->data[--this->current_index];
        }
        return this->data[this->current_index];
    }
    void _moveTo(int index) {
        if (index >= this->size) {
            index = this->size - 1;
        } else if (index < 0) {
            index = 0;
        }
        this->current_index = index;
    }
}
class Array<T, int S = 0> {
    T* data;
    int size;
    Array() {
        this->data = nullptr;
        this->size = 0;
    }
    void operator[]=(T* data, int length) {
        if (length > S) {
            this->size = length;
        } else {
            this->size = S;
        }
        this->data = `malloc(sizeof "T" * this->size);
        for (int i = 0; i < this->size; i++) {
            this->data[i] = data[i];
        }
    }
    T operator[](int index) {
        return this->data[index];
    }
    ArrayIterator<T> _begin() {
        return ArrayIterator<T>(this->data, this->size, false);
    }
    ArrayIterator<T> _end() {
        return ArrayIterator<T>(this->data, this->size, true);
    }
}
```

A good and recommended design convention which follows the languages conventions is this:
```qc
namespace MyType {
    namespace Iterator {
        class It ...
    }
    class MyTy ...
}
```
So your type namespace has a nested namespace with the iterator.
