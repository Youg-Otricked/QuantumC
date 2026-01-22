<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Functions

[Back to Home](./index.md)

A function is a block of code you can call over and over again. They don't add new *power* to the language (mostly), but they are very useful for a core paradigm of programming: Having one source of truth, also known as having code that is DRY(Don't Repeat Yourself). The reason having DRY/OST code is that you only have to worry about one thing. Let's say your refactoring your code(changing it to allow somthing new). It is way easier to change(or not forget to change) let's say, the way it adds with code like this:
```cpp
//function that adds

int main() {
    //call add
    //call add
    //call add
}
```
Than with code like this
```cpp
int main() {
    //code that adds1
    //code that adds2
    //code that adds3
}
```

You define a function with the syntax return-type name(optional-arg-list) { code }
The argument list is a comma-separated list of type name pairs, and can be empty.
So a function that takes 2 integers as argument and returns them added together will look like
```cpp
int add(int a, int b) {
    return a + b;
}
```
Couple of clarifications:
- you could name it anything, not necessarily add. 
- Return does 2 things:
    - Exits the function instantly. 
    - Outputs that value to any variable waiting to catch it outside the function. That value must be the same as the return type (in that signature, int).
You can also have no arguments, or no return type. If you want no return type, then you actually write the type `void`. EG
```cpp
void print_name() {
    print("Name");
}
```
You can run the code in functions by typing the functions name followed by parenthesis and the values you want to pass to the function, so in the case of the add function a bit above, to add 2 and 2 you would call:
```cpp
add(2, 2);
```
and to catch the returned result you would do
```cpp
int a = add(2, 2);
```
As you see, you can have any number of arguments. Later, I will cover some more advanced concepts.