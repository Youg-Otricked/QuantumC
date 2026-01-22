<link rel="stylesheet" href="{{ '/assets/css/main.css' | relative_url }}">

# Loops

[Back to Home](./index.md)

### Loop types

|////|Use|Syntax|Pro/Con|
|----|---|------|-------|
|**while**|The basic loop|while (condition) { code }|The easiest to understand|
|**for**|While with a twist|for(init;condition;step) { code }|More complex, more useful|
|**foreach**|Iterate through collections easily|foreach (type name in collection) {code}|Less usefull than for, very simple syntax|

### Syntax And examples

```cpp
int main() {
    bool flag = true;
    int i = 0;
    while(flag) {
        i++;
        if (i >= 100) {
            flag = false;
        }
    } // This loop will run 100 times, because on the 100'th occurence, i will = 100, and flag will be set to false
}
```

Why for loops are more useful and complex is obvious:
```cpp
int main() {
    // for syntax is for(init; condition; step)
    // this is the exact same as the loop above
    for (int i = 0; i < 100; i++) {
        // No code
    }
    // for combines the iterator and the increment steps
    // That above code's first step, the initilization creates a variable, i, and sets it to 0, then it will run the step and code while the condition is true
    // iterating through a list
    int[] lst = [1, 2, 3, 4, 5];
    for (int i = 0; i < lst.length; i++) {
        std::qout << lst[i] << '\n';
    } // The loop stops once i has iterated through all indexes because i is the index as indexes start at 0
}
```

Foreach loops are obviously less useful, but easier and sometimes better
```cpp
int main() {
    int[] example = [1, 56, 3, 66, 3, 2];
    foreach (int i in example) {
        std::qout << i << '\n';
    } // Prints all elements in the list. Exact same as iterating with for and an index.
}
```