class ArrayIterator<T> {
    T* data;
    int size;
    int current_index;
    ArrayIterator(T* data, int size, bool is_end) {
        this.data = data;
        this.size = size;
        this.current_index = ternary(is_end, size - 1, 0);
    }
    bool _atEnd() {
        return this.size <= this.current_index;
    }
    T _next() {
        if (!this._atEnd()) {
            return this.data[this.current_index++];
        }
        return this.data[this.current_index];
    } 
    bool _atStart() {
        return this.current_index <= 0;
    }
    T _prev() {
        if (!this._atStart()) {
            return this.data[--this.current_index];
        }
        return this.data[this.current_index];
    }
    void _moveTo(int index) {
        if (index >= this.size) {
            index = this.size - 1;
        } else if (index < 0) {
            index = 0;
        }
        this.current_index = index;
    }
}
class Array<T, int S = 0> {
    T* data;
    int size;
    Array() {
        this.data = nullptr;
        this.size = 0;
    }
    void operator[]=(T* data, int length) {
        if (length > S) {
            this.size = length;
        } else {
            this.size = S;
        }
        this.data = malloc(sizeof "T" * this.size);
        for (int i = 0; i < this.size; i++) {
            this.data[i] = data[i];
        }
    }
    T operator[](int index) {
        return this.data[index];
    }
    ArrayIterator<T> _begin() {
        return ArrayIterator<T>(this.data, this.size, false);
    }
    ArrayIterator<T> _end() {
        return ArrayIterator<T>(this.data, this.size, true);
    }
}
int main() {
    Array<int, 2> x = [1, 2];       
    foreach (int elem in x) {
        qout("%i", elem);
    }
    return 0;
}
