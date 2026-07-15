class Pair<T, V> {
    T first;
    V second;
    Pair(T f, V s) {
        this->first = f;
        this->second = s;
    }
    T getFirst() {
        return this->first;
    }
    V getSecond() {
        return this->second;
    }
    T swapMethod<M>(M other) {
        return this->first;
    }
}

struct Point<T> {
    T x;
    T y;
}

class Vector<T, int S> {
    T data[S];
    Vector() {}
    T get(int i) {
        return this->data[i];
    }
    void set(int i, T val) {
        this->data[i] = val;
    }
}

class Box<T> {
    T* ptr;
    Box(T* p) {
        this->ptr = p;
    }
    T get() {
        return *this->ptr;
    }
}

class Variant<...Tys> {
}

T identity<T>(T val) {
    return val;
}

int add<T(:numeric)>(T a, T b) {
    return a + b;
}

T cloneUserType<T(usertype:)>(T val) {
    return val;
}

int main() {
    Pair<int, string> p = Pair<int, string>(42, "hello");
    qout("%i", p.getFirst());
    qout("%s", p.getSecond());
    qout("%i", p.swapMethod<string>("world"));

    Pair<string, int> p2 = Pair<string, int>("world", 99);
    qout("%s", p2.getFirst());
    qout("%i", p2.getSecond());

    Pair<List<int>, string> p3 = Pair<List<int>, string>(List<int>(), "nested");
    qout("%s", p3.getSecond());

    Point<int> pt;
    pt.x = 10;
    pt.y = 20;
    qout("%i", pt.x);

    Vector<int, 4> v = Vector<int, 4>();
    v.set(0, 99);
    qout("%i", v.get(0));

    int x = 42;
    Box<int> b = Box<int>(&x);
    qout("%i", b.get());

    Variant<int, string, float> var;

    qout("%i", identity<int>(123));
    qout("%s", identity<string>("abc"));

    qout("%i", add<int>(3, 4));
    qout("%i", add<float>(1.5, 2.5));

    Pair<int, string> clone = cloneUserType<Pair<int, string>>(p);
    qout("%i", clone.getFirst());

    return 0;
}
