class GenericPoint<V(numeric:), H(:int|double)> {
    V x;
    H y;
    GenericPoint() {
        this.x = 123;
        this.y = 123;
    }
    V getX() {
        return this.x;
    }
    void setX(V val) {
        this.x = val;
        return;
    }
}
class Box<T> {
    T value;
    Box() {
    }
    T get() {
        return this.value;
    }
}
class Node<T> {
    Node<T>* next;
    Node() {
    }
    void setNext(Node<T>* next) {
        this.next = next;
        return;
    }
}
class Vector<T> {
    T *data;
    int length;
    Vector() {
    }
    void operator[]=(T* init, int length) {
        this.data = calloc(length, sizeof "T");
        this.length = length;
        for (int i = 0; i < length; i++) {
            this.data[i] = init[i];
        }
    }
    T& operator[](int index) {
        return this.data[index];
    }
}
int main() {
    GenericPoint<int, int> p1 = GenericPoint<int, int>();
    GenericPoint<double, double> p2 = GenericPoint<double, double>();
    qout("%i, %i", p1.x, p1.y);
    int x = p1.getX();
    qout("%i", x);
    p1.setX(42);
    qout("%i", p1.x);
    Node<int> node = Node<int>();
    Node<int> node2 = Node<int>();
    node.setNext(&node2);
    node2.setNext(&node);
    int raw_x = p1.x;
    qout("%i", raw_x);
    Box<int> b1 = Box<int>();
    Box<double> b2 = Box<double>();
    int bval = b1.get();
    double bval2 = b2.get();

    Vector<int> v = Vector<int>();
    v = [1, 2, 3];
    qout("%i", v[1]);
    return 0;
}
