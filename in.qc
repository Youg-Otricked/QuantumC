class thing {
    int a;
    thing(int a) {
        this.a = a;
    }
    void init() {
        this.a = 0;
    }
}
struct test {
    int a;
    int b;
}
int main() {
    thing b = thing(20);
    thing a;
    test tester;
}