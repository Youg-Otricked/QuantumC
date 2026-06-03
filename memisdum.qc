namespace Exported {
    #include <UnitTest, ./stdlib.qc>
}
struct Point {
    int x;
    int y;
}
void add(int& x, int y) {
    x += y;
}
void aAutoReturn(int& x, auto y) {
    if (typeof(y) == "int") {
        x += y;
    }
}
void addToX(Point& x, int y) {
    x.x += y;
}
class Refs {
    int x;
    Refs(int x) {
        this.x = x;
    }
    void getX(int& y) {
        y = this.x;
    }
    void setXp1(int& t) {
        t += 1;
        this.x = t;
    }
    void autoRet(int& x, auto y) {
        if (typeof(y) == "int") {
            x += y;
        }
    }
    Refs& operator=(Refs other) {
        this.x = other.x;
        return this;
    }
}
class Node {
    int value;
    Node* next;

    Node(int val) {
        this.value = val;
        this.next = nullptr;
    }

    void setNext(Node* n) {
        this.next = n;
    }
}
void increment(int* p) {
    *p = *p + 1;
}
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
void autoPointer(auto* p) {
    *p = *p * 2;
}
int TESTESTESTESTESTEST() {
    UnitTest::Test test = UnitTest::Test(6);
    int val = 10;
    increment(&val);
    test.AssertEqual(11, val, "ptr param increment", "val == 11");
    int x = 1;
    int y = 2;
    swap(x, y);
    test.AssertEqual(2, x, "ref swap x", "x == 2");
    test.AssertEqual(1, y, "ref swap y", "y == 1");
    int magic = 50;
    autoPointer(&magic);
    test.AssertEqual(100, magic, "auto ptr doubling", "magic == 100");
    Node n1 = Node(10);
    Node n2 = Node(20);
    n1.setNext(&n2);
    Node* temp = n1.next;
    int nextVal = temp->value;
    test.AssertEqual(20, nextVal, "pointer property access", "(*n1.next).value == 20");
    n1.next->value = 42;
    test.AssertEqual(42, n2.value, "pointer property update", "n2.value == 42");
    int *ptr = nullptr;
    int* *ptr_ptr = nullptr;
    int** *ptr_ptr_ptr = nullptr;
    ptr = &x;
    ptr_ptr = &ptr;
    ptr_ptr_ptr = &ptr_ptr;
    qout("%p, %p, %p, %i", ptr_ptr_ptr, *ptr_ptr_ptr, **ptr_ptr_ptr, ***ptr_ptr_ptr);
    return 0;
}
class Node2 {
    int value;
    Node2* next;
    Node2(int val, Node2* next) {
        this.next = next;
        this.value = val; 
    }
}

class Warrior {
    int hp;
    Warrior(int hp) {
        this.hp = hp;
    }
}

void test_nullptr() {
    Node2* n = nullptr;
    Warrior* w = nullptr;
    int* p = nullptr;
    if (n == nullptr) {
        qout("Success: n is null");
    } else {
        qout("Fail: n is not nullptr");
    }
    Node2 nod = Node2(10, nullptr);
    Node2* real_node = &nod;
    if (real_node != nullptr) {
        qout("Success: real_node is not null");
    }
    real_node->next = nullptr;
    n = real_node;
    n = nullptr;
}
void final_ptr_test() {
    int x = 10;
    int y = 20;
    int z = 30;
    int* p = &x;
    if (p[0] == 10) {
        qout("Success: p[0] is 10");
    }
    int* p2 = p - 1; 
    p2[0] = 99;
    if (y == 99 || z == 99) {
        qout("Success: Offset assignment worked");
    }
    int* p_start = &x;
    int* p_end = p_start + 5;
    int dist = p_end - p_start;
    if (dist == 5) {
        qout("Success: Pointer distance is 5");
    }
    int* n = nullptr;
    int* n2 = n + 10;
    if (n2 != nullptr) {
        qout("Success: nullptr + 10 is not null");
    }
    int val = 0;
    int* arr_ptr = &val;
    int i = 0;
    while (i < 5) {
        arr_ptr[0] = i; 
        i = i + 1;
    }
    if (val == 4) {
        qout("Success: Loop indexing worked");
    }
}
int main() {
    UnitTest::Test test = UnitTest::Test(8);
    int y = 0;
    int& rx = y;
    rx = 12345;
    test.AssertEqual(12345, rx, "expected rx to equal 12345", "rx == 12345");
    test.AssertEqual(12345, y, "expected x to equal 12345", "x = 12345; x == 12345");
    int n = 1234;
    add(y, n);
    test.AssertEqual(13579, y, "expected x to equal 13579", "x == 13579");
    Refs r = Refs(12345);
    Refs z = Refs(321);
    Refs x = Refs(21);
    x = z = r;
    x.getX(y);
    test.AssertEqual(12345, y, "expected x = 12345", "x == 12345");
    x.setXp1(y);
    aAutoReturn(y, n);
    x.autoRet(y, n);
    test.AssertEqual(14814, y, "expected x = 14814", "x == 14814");
    Point pnt = {1, 3};
    addToX(pnt, 21);
    test.AssertEqual(22, pnt.x, "expected pnt.x to be 22", "pnt.x == 22");
    int* py = &y;
    int ptr_deref = *py;
    test.AssertEqual(14814, ptr_deref, "expected ptr_deref to be 14814", "ptr_deref == 14814");
    *py += 123;
    test.AssertEqual(14937, *py, "expected *py to be 14937", "ptr_deref == 14814");
    TESTESTESTESTESTEST();
    test_nullptr();
    final_ptr_test();
    return 0;
}