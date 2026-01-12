# Collection datatypes
[Home](./index.md)

The available collection types are list, map, and array. The syntax is:
```cpp
int main() {
    int[] ListEx = [1, 2, 3, 4, 5]; // Lists use the syntax type[] name and are non-fixed size collections of a type
    int ArrayEx[5] = [1, 2, 3, 4, 5]; // Arrays use the syntax type name[] and are fixed size collections of a type
    map<string, int> MapIds = { "": 0, "all numbers": 1234567890}; // Maps are key -> value mapings of type1 -> type2.
    // Arrays have no methods and the property length which returns the size of the array
    int Size = ArrayEx.length;
    // Lists have the methods push and pop and the property length
    int ListSize = ListEx.length; // ListSize will be the size of ListEx
    ListEx.push(6); // ListEx now contains 1 2 3 4 5 and 6
    ListEx.pop(); // ListEx now is 1 2 3 4 5 again

    // Both arrays and lists have somthign called spread.
    int[] SpreadFusion = [@ArrayEx, 6, 7, 8, 9, 10]; // SpreadFusion is now 1 2 3 4 5 6 7 8 9 10; You can spread arrays in lists and vice versa or same in same.
    // Meanwhile if you do
    int[] NotSpread = [ArrayEx, 6, 7, 7, 9, 10];
    // then notspread is [[1, 2, 3, 4, 5], 6, 7, 8, 9, 10] which is an error if you do it in an array
    // Maps have 1 property, size, and many methods
    int MapSize = MapIds.size; // MapSize is now the number of keys in MapIds
    // You can assign a key to a map in 2 ways.
    MapIds["Me"] = 123; // This works
    // OR
    MapIds.set("Me", 12321) // This works. both work for setting and resetting, hence why this won't error
    MapIds.remove(""); // Remove removes the key and value of arg from the map
    MapIds.has(""); // Returns true if key exists, otherwise returns false
    string[] MapsKeys = MapIds.keys(); // Returns a array of the keys in MapIds
}
```