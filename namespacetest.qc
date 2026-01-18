// @print-ast
namespace Outer {
    int outerVar = 10;

    namespace Inner {
        int innerVar = 20;
        
        int getInner() {
            return innerVar;
        }
        int getoi() {
            return outerVar;
        }
    }

    int getOuter() {
        return outerVar;
    }

    namespace Inner2 {
        int inner2Var = 30;
    }

    enum Color {
        Red = 0;
        Green = 1;
        Blue = 2;
    }

    type MyUnion = int | float;

    type AliasInt = int;
}
namespace Inner {
    class InnerClass {
        int y;
        InnerClass(int y) {
            this.y = y;
        }
        int getY() { return this.y; }
    }
}

int main() {
    int globalVar = 1;
    // Access global
    globalVar = 2;

    // Access outer + inner
    Outer::outerVar = 100;
    Outer::Inner::innerVar = 200;

    // Call functions
    int a = Outer::getOuter();
    int b = Outer::Inner::getInner();


    // Struct using namespace member type

    // Enums
    Outer::Color col = Outer::Color.Red;

    // Union
    Outer::MyUnion u;
    u = 42;

    // Inner class
    Inner::InnerClass ic = Inner::InnerClass(123);
    int iy = ic.getY();

    return a + b + col + u + Outer::Inner::getoi();
}