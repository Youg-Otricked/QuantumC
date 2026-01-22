<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Advanced Function features

[Back to Home](./index.md)

There are 3 more important function features. Default arguments, multi returns, and Lambdas.
Default arguments use this syntax.
```cpp
void greet(string name = "World") {
    std::qout << "Hello, " << name << '\n';
}
```
Now, if you call the function with syntax
```cpp
greet("Me");
```
it would print 
```
Hello, Me
```
But if you called with
```cpp
greet();
```
It would output
```
Hello, World
```

Multi returns syntax is the same as normal functions, but you type multiple returns with syntax type, type, ...
```cpp
int, string get_stats() {
    return 10, "Stuff";
}
```
Very simmilar, but using commas.
To capture the result you would use
```cpp
int number, string result = get_stats();
```

Finally, there are lambdas. Lambdas are variables that hold functions, or nameless functions

```cpp
fn(int a) -> int {
    return a;
}(123);
```
Is a immedietly invoked lambda. it instantly calls it.
```cpp
function func = fn(int a) -> int {
    return a;
};
```
Stores the fn in a variable. 

You use this syntax to make a lambda:
```cpp
fn(arg-list) -> returntypes {
    code
};
```

and you call lambdas in vars just like you call normal functions