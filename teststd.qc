namespace Exported {
    #include <AdvQBool, std>
}
int main() {
    AdvQBool::AQB test = AdvQBool::AQB(70);
    if (test) {
        println(test);
    }
    if (test) {
        println(test);
    }
    if (test && true) {
        println(test);
    }
    if (!test) {
        println(test);
    }
    if (test || false) {
        println(test);
    }
    test = 50;
    if (test) {
        println(test);
    }
    if (test ^ true) {
        println(test);
    }
    if (test) {
        println(test);
    }
    return 0;
}