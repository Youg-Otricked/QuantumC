<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Namespaces

[Back to Home](./index.md)


## Namespaces
Namespaces are another important feature in Quantum C. Namespaces are a collection of **_Variables_ and _Functions_** **ONLY**. Computation outside functions in a namespace is strictly _prohibited_.
You make a namespace with this syntax:
```cpp
namespace NamespaceName {
    // Stuff goes here
}
```
Thats it. However accessing items in namespaces is slightly more complex.

You access namespaces fields with as follows:
```cpp
Namespacename::fieldname
```
:: is somthing called the _Scope resolution operator_. What it does is it basically takes you into the scope of that namespace. Let's say we have a namespace Outer, a namespace Inner, and a Field DeepField we want to access. What we do to access this is as follows:
```cpp
Outer::Inner::DeepField
// Outer:: takes you into the outer namespace scope
// Now that we are in outer we can do Inner::
// Now this variable we are accessing is on the Outer::Inner scope.
// To acces it we just type the name
// Inner::DeepField would error because that namespace doesn't exist in this scope.
// Outer::DeepField also errors because that variable is not declared in the Outer:: scope.
```