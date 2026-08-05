<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Try/Catch

[Back to Home](./index.md)

C^4 defer makes somthing run at the end of a scope

```
int x = 0;
int main() {
    if (true) {
        defer x = 0;
        x = 321;
    }
    // x is 0;
}
```

The unique thing about C^4 defer compared to defer in a language like go is that during Try/Catch and throw, your defer statements WILL NOT RUN. This is to avoid the additional runtime cost.

```qc
int x = 21;
int main() {
    try {
        defer x = 0;
        throw 12;
    } catch (int z) {
        // x is still 21
    }
}
```
