namespace Array {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this.data = data;
                this.size = size;
                this.current_index = ternary(is_end, size, 0);
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
    }
    class Arr<T, int S = 0> {
        T* data;
        int size;
        Arr() {
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
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this.data, this.size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this.data, this.size, true);
        }
        void _destroy() {
            free(this.data);
            this.data = nullptr;
            this.size = -1;
        }
        Arr<T, S> operator=(Arr<T, S> other) {
            if (other.size != this.size) {
                return Arr();
            }
            for (int i = 0; i < other.size; i++) {
                this.data[i] = other.data[i];
            }
            return this;
        }
    }
}
namespace Vector {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this.data = data;
                this.size = size;
                this.current_index = ternary(is_end, size, 0);
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
    }
    class Vec<T> {
        T* data;
        int size;
        int capacity;
        Vec() {
            this.size = 0;
            this.capacity = 0;
            this.data = nullptr;
        }
        void reserve(int cap) {
            if (cap == 0) {
                free(this.data);                
                this.data = nullptr;
                this.capacity = 0;
                this.size = 0;
                return;
            }

            T* new_data = realloc(this.data, sizeof "T" * cap);
            if (new_data == nullptr) {
                return;
            }
            this.capacity = cap;
            if (this.size > this.capacity) {
                this.size = this.capacity;
            }
            this.data = new_data;
        }
        void push(T value) {
            if (this.capacity <= this.size) {
                this.reserve(ternery(this.capacity == 0, 1, this.capacity * 2));
                if (this.data == nullptr) return;
            }
            this.data[this.size] = value;
            this.size++;
        }
        void pop() {
            if (this.size > 0) {
                this.size--;
            }
        }
        void shrinkToFit() {
            this.reserve(this.size);
        }
        void operator[]=(T* data, int length) {
            this.capacity = length;
            this.size = length;
            this.data = malloc(sizeof "T" * this.capacity);
            for (int i = 0; i < this.size; i++) {
                this.data[i] = data[i];
            }
        }
        T operator[](int index) {
            return this.data[index];
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this.data, this.size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this.data, this.size, true);
        }
        void _destroy() {
            free(this.data);
            this.data = nullptr;
            this.size = -1;
            this.capacity = -1;
        }
        Vec<T> operator=(Vec<T> other) {
            if (other.capacity != this.capacity) {
                this.reserve(other.capacity);
            }
            this.size = other.size;
            for (int i = 0; i < other.size; i++) {
                this.data[i] = other.data[i];
            }
            return this;
        }
        bool isEmpty() {
            return this.size == 0;
        }
    }
}
namespace List {
    class Node<T> {
        T data;
        Node<T>* next;
        Node<T>* prev;

        Node(T data) {
            this.data = data;
            this.next = nullptr;
            this.prev = nullptr;
        }
    }

    namespace Iterator {
        class It<T> {
            Node<T>* current;

            It(Node<T>* node) {
                this.current = node;
            }

            bool _atEnd() {
                return this.current == nullptr;
            }

            T _next() {
                T value = this.current->data;
                this.current = this.current->next;
                return value;
            }

            bool _atStart() {
                return this.current->prev == nullptr;
            }

            T _prev() {
                T value = this.current->data;
                this.current = this.current->prev;
                return value;
            }
        }
    }

    class List<T> {
        Node<T>* head;
        Node<T>* tail;
        int size;
        List() {
            this.head = nullptr;
            this.tail = nullptr;
            this.size = 0;
        }
        bool isEmpty() {
            return this.size == 0;
        }
        T front() {
            return this.head->data;
        }
        T back() {
            return this.tail->data;
        }
        void pushFront(T value) {
            Node<T>* node = malloc(sizeof "Node<T>");
            node = Node<T>(value);

            node.next = this.head;
            if (this.head != nullptr) {
                this.head->prev = node;
            } else {
                this.tail = node;
            }
            this.head = node;
            this.size++;
        }
        void pushBack(T value) {
            Node<T>* node = malloc(sizeof "Node<T>");
            node = Node<T>(value);
            node.prev = this.tail;
            if (this.tail != nullptr) {
                this.tail->next = node;
            } else {
                this.head = node;
            }
            this.tail = node;
            this.size++;
        }
        void popFront() {
            if (this.head == nullptr) {
                return;
            }
            Node<T>* old = this.head;
            this.head = this.head.next;
            if (this.head != nullptr) {
                this.head.prev = nullptr;
            } else {
                this.tail = nullptr;
            }
            free(old);
            this.size--;
        }
        void popBack() {
            if (this.tail == nullptr) {
                return;
            }
            Node<T>* old = this.tail;
            this.tail = this.tail->prev;
            if (this.tail != nullptr) {
                this.tail->next = nullptr;
            } else {
                this.head = nullptr;
            }
            free(old);
            this.size--;
        }
        void clear() {
            Node<T>* current = this.head;
            while (current != nullptr) {
                Node<T>* next = current.next;
                free(current);
                current = next;
            }
            this.head = nullptr;
            this.tail = nullptr;
            this.size = 0;
        }
        bool contains(T value) {
            Node<T>* current = this.head;
            while (current != nullptr) {
                if (current.data == value) {
                    return true;
                }
                current = current.next;
            }
            return false;
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this.head);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(nullptr);
        }
        void _destroy() {
            this.clear();

            this.head = nullptr;
            this.tail = nullptr;
            this.size = -1;
        }
        List<T> operator=(List<T> other) {
            this.clear();

            Node<T>* current = other.head;

            while (current != nullptr) {
                this.pushBack(current.data);
                current = current.next;
            }

            return this;
        }
    }
}
int main() {
}
