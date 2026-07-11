class A {
    int add(int a) {
        return a + 2;
    }
    A() {
    }
}
class B : A {
    int add(int a, int b) {
        return a + b;
    }
    B() {
    }
}
int main() {
    A a = A();
    A* aClass = &a;
    qout("%i", aClass->add(123));
    B b = B();
    aClass = &b;
    qout("%i", aClass->add(123, 321));
    return 0;
} // just need to handle the actusal method calls
