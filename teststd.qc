namespace Exported {
    #include <AdvQBool, std>
    #include <Utils, std>
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
    foreach (int i in Utils::range(1, 10, 1)) {
        std::qout << i << '\n';
    }
    return 0;
}