// string_vs_pointer.qc

int* give_int_ptr(int* p) {
    return p;
}

string give_string() {
    return "returned string";
}

class Box {
    string label;
    int value;

    string get_label() {
        return this.label;
    }
}

int main() {
    println("=== STRING VS POINTER TESTS ===");

    int x = 42;
    int* px = &x;
    string s = "hello";
    Box b;
    b.label = "box label";
    b.value = 99;

    list<string> ls = ["a", "b", "c"];
    map<string, int> m = {"Alice": 1, "Bob": 2};

    println("--- 1. raw string literal ---");
    println("literal string");

    println("--- 2. string variable ---");
    println(s);

    println("--- 3. int pointer variable ---");
    println(px);

    println("--- 4. address of int ---");
    println(&x);

    println("--- 5. function returning string ---");
    println(give_string());

    println("--- 6. function returning raw pointer ---");
    println(give_int_ptr(px));

    println("--- 7. class string field ---");
    println(b.label);

    println("--- 8. method returning string ---");
    println(b.get_label());

    println("--- 9. list<string> direct index ---");
    println(ls[0]);
    println(ls[1]);

    println("--- 10. foreach over list<string> ---");
    foreach (string item in ls) {
        println(item);
    }

    println("--- 11. map<string, int> keys ---");
    foreach (string key in m.keys()) {
        println(key);
    }

    println("--- 12. string concatenation ---");
    println("hi " + s);

    println("--- 13. nested string expression ---");
    println("value: " + b.get_label());

    println("--- 14. pointer stored in variable then printed ---");
    int* py = px;
    println(py);

    println("--- 15. address of string variable (should be pointer-ish, not string) ---");
    println(&s);

    println("--- 16. string from conditional/assigned expression substitute ---");
    string chosen = "chosen";
    println(chosen);

    println("--- DONE ---");
    return 0;
}