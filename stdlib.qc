// This is the Quantum C Standerd Library
// Bro why u readin this do i need to make my docs beter?

int main() {
    `qout("Quantum C Standerd Lib. Don't run this file. include from it\n");
    return 0;
}
namespace Exported {
}
namespace AdvQBool {
    type AlTypes = qbool | bool | AQB;
    class AQB {
        int TruthLevel;
        int FalseLevel;
        AQB(int truth) {
            if (truth > 100 || truth < 0) {
                //throw("Cannot make a advanced qbool more than 100 percent true or more than 100% false.");
                if (truth > 100) {
                    truth = 100;
                } else {
                    truth = 0;
                }
            }
            this.TruthLevel = truth;
            this.FalseLevel = 100 - truth;
        }
        void operator=(int other) {
            if (other > 100 || other < 0) {
                //throw("Cannot make a advanced qbool more than 100 percent true.");
                if (other > 100) {
                    other = 100;
                } else {
                    other = 0;
                }
            }
            this.TruthLevel = other;
            this.FalseLevel = 100 - other;
        }
        bool operator&&(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this._eval() && other._eval();
            } else {
                return this._eval() && other;
            }
        }
        bool operator||(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this._eval() || other._eval();
            } else {
                return this._eval() || other;
            }
        }
        bool operator^(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this._eval() ^ other._eval();
            } else {
                return this._eval() ^ other;
            }
        }
        bool operator!() {
            return !this._eval();
        }
        bool _eval() {
            if (`random(0, 100) < this.FalseLevel) {
                return false;
            } else {
                return true;
            }
        }
        string _repr() {
            return f"Advanced QBool is {this.TruthLevel} true and {this.FalseLevel} false.";
        }
    }
}
namespace Array {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this.data = data;
                this.size = size;
                this.current_index = `ternary(is_end, size, 0);
            }
            bool _atEnd() {
                return this.size <= this.current_index;
            }
            T _next() {
                if (!this._atEnd()) {
                    return this.data[this.current_index++];
                }
                return this.data[this.size - 1]; 
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
            `free(this.data);
            if (S == 0) {
                this.size = length;
            } else {
                this.size = `ternary((length > S), S, length);
            }
            this.data = `malloc(sizeof "T" * this.size);
            for (int i = 0; i < this.size; i++) {
                this.data[i] = data[i];
            }
        }
        T& operator[](int index) {
            return this.data[index];
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this.data, this.size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this.data, this.size, true);
        }
        void _destroy() {
            `free(this.data);
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
                this.current_index = `ternary(is_end, size, 0);
            }
            bool _atEnd() {
                return this.size <= this.current_index;
            }
            T _next() {
                if (!this._atEnd()) {
                    return this.data[this.current_index++];
                }
                return this.data[this.size - 1];
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
                `free(this.data);                
                this.data = nullptr;
                this.capacity = 0;
                this.size = 0;
                return;
            }

            T* new_data = `realloc(this.data, sizeof "T" * cap);
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
                this.reserve(`ternary(this.capacity == 0, 1, this.capacity * 2));
                if (this.data == nullptr) return;
            }
            this.data[this.size] = value;
            this.size++;
        }
        int length() {
            return this.size;
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
            `free(this.data);
            this.capacity = length;
            this.size = length;
            this.data = `malloc(sizeof "T" * this.capacity);
            for (int i = 0; i < this.size; i++) {
                this.data[i] = data[i];
            }
        }
        T& operator[](int index) {
            return this.data[index];
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this.data, this.size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this.data, this.size, true);
        }
        void _destroy() {
            `free(this.data);
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
        private Node<T>* _getNode(int index) {
            if (index < 0 || index >= this.size) {
                return nullptr;
            }
            Node<T>* current;
            if (index < this.size / 2) {
                current = this.head;
                for (int i = 0; i < index; i++) {
                    current = current->next;
                }
            } else {
                current = this.tail;
                for (int i = this.size - 1; i > index; i--) {
                    current = current->prev;
                }
            }
            return current;
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
            Node<T>* node = `malloc(sizeof "Node<T>");
            *node = Node<T>(value);
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
            Node<T>* node = `malloc(sizeof "Node<T>");
            *node = Node<T>(value);
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
            this.head = this.head->next;
            if (this.head != nullptr) {
                this.head->prev = nullptr;
            } else {
                this.tail = nullptr;
            }
            `free(old);
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
            `free(old);
            this.size--;
        }
        void clear() {
            Node<T>* current = this.head;
            while (current != nullptr) {
                Node<T>* next = current->next;
                `free(current);
                current = next;
            }
            this.head = nullptr;
            this.tail = nullptr;
            this.size = 0;
        }
        bool contains(T value) {
            Node<T>* current = this.head;
            while (current != nullptr) {
                if (current->data == value) {
                    return true;
                }
                current = current->next;
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
        T& operator[](int index) {
            Node<T>* node = this._getNode(index);
            if (node == nullptr) {
                return nullptr;
            }
            return node.data;
        }
        void operator[]=(T* data, int length) {
            this.clear();
            for (int i = 0; i < length; i++) {
                this.pushBack(data[i]);
            }
        }
        List<T> operator=(List<T> other) {
            this.clear();

            Node<T>* current = other.head;

            while (current != nullptr) {
                this.pushBack(current->data);
                current = current->next;
            }

            return this;
        }
    }
}
#depends(Utils: Vector)
namespace Utils {
    Vector::Vec<int> range(int start, int stop, int step = 1) {
        Vector::Vec<int> fin = Vector::Vec<int>();
        if (step > 0 && start <= stop) {
            for (; start < stop; start += step) {
                fin.push(start);
            }
        }
        else if (step < 0 && start >= stop) {
            for (; start > stop; start += step) {
                fin.push(start);
            }
        }
        else {
            return Vector::Vec<int>();
        }
        return fin;
    }
    struct _timespec {
        long int rem_sec;
        long int rem_nsec;
    }
    volatile void sleep(long int milliseconds) {
        volatile long int req[2] = [milliseconds / 1000, (milliseconds % 1000) * 1000000];
        volatile _timespec rem = {0, 0};
        while (true) {
            volatile long int result = 0;
            `inline(R"(
                mov rax, 230
                mov rdi, 1
                mov rsi, 0
                mov rdx, $1r
                mov r10, $2r
                syscall
                mov $0=r, rax
            )", result, &req[0], &(rem.rem_sec), "~{rax}~{rdi}~{rsi}~{rdx}~{r10}~{rcx}~{r11}");
            if (result == 0) {
                break;
            }
            if (result == -4) {
                req[0] = rem.rem_sec;
                req[1] = rem.rem_nsec;
                continue;
            }
            break;
        }
    }
}
namespace Math {
    double e() {
        return 2.71828182845904523536;
    }
    
    double pi() {
        return 3.14159265358979323846;
    }
    type Number = int | float | double;
    Number max(Number a, Number b) {
        if (a > b) {
            return a;
        }
        return b;
    }
    Number min(Number a, Number b) {
        if (a > b) {
            return b;
        }
        return a;
    }
    Number sqrt(Number val) {
        return `to_double(val) #^ 0.5;
    }
    Number root(Number val, Number power) {
        double base = `to_double(val);
        double exp  = 1.0 / `to_double(power);
        return base #^ exp;
    }
    type Floating = float | double;
    int ceil(Floating a) {
        double d = `to_double(a);
        int i = `to_int(d);
        if (d == `to_double(i)) {
            return i;
        } else if (d > 0) {
            return i + 1;
        } else {
            return i;
        }
    }
    int floor(Floating a) {
        double d = `to_double(a);
        int i = `to_int(d);
        if (d >= 0) {
            return i;
        } else {
            if (d == `to_double(i)) {
                return i;
            } else {
                return i - 1;
            }
        }
    }
    Number abs(Number a) {
        if (a < 0) {
            return a * -1;
        }
        return a;
    }
    double sin(double x) {
        double pi = 3.14159265358979323846;
        while (x > pi) { x -= 2 * pi; }
        while (x < -pi) { x += 2 * pi; }
        
        double result = 0.0;
        double term = x;
        int n = 1;
        for (int i = 0; i < 10; i++) {
            result += term;
            term *= -1.0 * x * x / ((2 * n) * (2 * n + 1));
            n++;
        }
        
        return result;
    }
    double cos(double x) {
        
        double pi = 3.14159265358979323846;
        while (x > pi) { x -= 2 * pi; }
        while (x < -pi) { x += 2 * pi; }
        
        double result = 0.0;
        double term = 1.0;
        int n = 1;
        
        for (int i = 0; i < 10; i++) {
            result += term;
            term *= -1.0 * x * x / ((2 * n - 1) * (2 * n));
            n++;
        }
        
        return result;
    }
    double tan(double x) {
        return `ternary(sin(x) == 0.0 || cos(x) == 0.0, 0.0, sin(x) / cos(x));
    }
    double log(double x) {
        if (x <= 0) {
            //throw("log: x must be positive");
            return 0.0;
        }
        double log2 = 0.693147180559945309417;
        int n = 0;
        
        while (x > 2.0) {
            x /= 2.0;
            n++;
        }
        while (x < 0.5) {
            x *= 2.0;
            n--;
        }
        double y = x - 1.0;
        double result = 0.0;
        double term = y;
        
        for (int i = 1; i <= 20; i++) {
            result += term / `to_double(i);
            term *= -y;
        }
        
        return result + n * log2;
    }
}
namespace OSInterop {
    void system(string command) {
        `flush();
        `inline(R"(
        mov rdi, $0r
        call system
        )", command, "~{rdi}");
    }
}
