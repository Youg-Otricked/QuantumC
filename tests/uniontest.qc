class X {
    int x;
    X(){
    }
    int aMethod() {
        return 32;
    }
}
class Y {
    int y;
    Y(){
    }
    int aMethod() {
        return 12;
    }
}
int main() {
    type MyUnion = X | Y | int | string;
    MyUnion x = 123;
    qout("%s", typeof(x));
    x = X();
    qout("%s", typeof(x));
    x = Y();
    qout("%s", typeof(x));
    qout("%i, %i", x.aMethod(), X().aMethod());
}
