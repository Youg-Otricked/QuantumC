
<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Try/Catch

[Back to Home](./index.md)

Try/Catch in C^4 works similar to C++.

```qc
void throwsSomeStuff() {
    throw 123;
}
int main() {
    try {
        throwsSomeStuff();
    } catch (int e) {
        ...
    }
}
```

However nested try catch is not allowed, as it is additional obfuscation for no reason.
