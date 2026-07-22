<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

## Variadics

[Back to home](./index.md)

Variadics are simple. They just mean any amount of arguments can be passed to this function.

```
int addMany(...args) {
    int sum;
    while (!`is_empty(args)) {
        sum += `next(args, "int");
    }
    return sum;
}
```
`...args` declares a variadic argument (hence the ... the ... makes the argument variadic).
\`is_empty takes a variadic argument and returns if it has anything left to iterate over.
\`next takes a variadic argument and a stringified type and returns the next element casted to that type.

