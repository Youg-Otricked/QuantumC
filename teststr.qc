namespace Exported {
    #include <Utils, ./stdlib.qc>
}
int main() {
    println(len("hello"));           // 5
    println(to_lower("HELLO"));      // hello
    println(to_upper("hello"));      // HELLO
    println(substring("QuantumC", 0, 7)); // Quantum
    println(split("hello world", " "));    // ["hello","world"]
    println(join(split("a b c", " "), "-")); // a-b-c
    println(contains("hello", "ll"));   // true
    println(startswith("hello", "he")); // true
    println(endswith("hello", "lo"));   // true
    println(trim("  hi  "));             // hi
    println(replace("hello", "l", "L")); // heLLo
    println(time());
    Utils::sleep(3);
    println(time());
}
/*NEXT:
Math library expansion

Add:

floor

abs

pow

sin/cos/tan

log

rand
*/