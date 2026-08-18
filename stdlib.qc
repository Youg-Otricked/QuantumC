// This is the Quantum C Standerd Library
// Bro why u readin this do i need to make my docs beter?

int main() {
    `qout("Quantum C Standerd Lib. Don't run this file. include from it\n");
    return 0;
}
namespace Exported {
}
namespace CoreConcepts {
    concept Eq {
        1_of {
            bool operator==(Self other);
            bool operator==(Self self, Self other);
        }
    }
    concept Allocated {
        at_least 1_of {
            void _destroy();
            void _destroy(Self self);
        }
    }
}
namespace AdvQBool {
    type AlTypes = qbool | bool | AQB;
    class AQB {
        int TruthLevel;
        int FalseLevel;
        AQB(int truth) {
            if (truth > 100 || truth < 0) {
                throw "Cannot make a advanced qbool more than 100 percent true or more than 100% false.";
            }
            this->TruthLevel = truth;
            this->FalseLevel = 100 - truth;
        }
        void operator=(int other) {
            if (other > 100 || other < 0) {
                throw "Cannot make a advanced qbool more than 100 percent true.";
            }
            this->TruthLevel = other;
            this->FalseLevel = 100 - other;
        }
        bool operator&&(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this->_eval() && other._eval();
            } else {
                return this->_eval() && other;
            }
        }
        bool operator||(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this->_eval() || other._eval();
            } else {
                return this->_eval() || other;
            }
        }
        bool operator^(AlTypes other) {
            if (`typeof(other) == "AdvQBool::AQB") {
                return this->_eval() ^ other._eval();
            } else {
                return this->_eval() ^ other;
            }
        }
        bool operator!() {
            return !this->_eval();
        }
        bool _eval() {
            if (`random(0, 100) < this->FalseLevel) {
                return false;
            } else {
                return true;
            }
        }
        string _repr() {
            return f"Advanced QBool is {this->TruthLevel} true and {this->FalseLevel} false.";
        }
    }
}
#depends(Array: CoreConcepts)
namespace Array {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this->data = data;
                this->size = size;
                this->current_index = `ternary(is_end, size, 0);
            }
            bool _atEnd() {
                return this->size <= this->current_index;
            }
            T _next() {
                if (!this->_atEnd()) {
                    return this->data[this->current_index++];
                }
                return this->data[this->size - 1]; 
            } 
            bool _atStart() {
                return this->current_index <= 0;
            }
            T _prev() {
                if (!this->_atStart()) {
                    return this->data[--this->current_index];
                }
                return this->data[this->current_index];
            }
            void _moveTo(int index) {
                if (index >= this->size) {
                    index = this->size - 1;
                } else if (index < 0) {
                    index = 0;
                }
                this->current_index = index;
            }
        }
    }
    class Arr<T, int S = 0> {
        T* data;
        int size;
        Arr() {
            this->data = nullptr;
            this->size = 0;
        }
        void operator[]=(T* data, int length) {
            if (this->size != 0) `free(this->data);
            if (S == 0) {
                this->size = length;
            } else {
                this->size = `ternary((length > S), S, length);
            }
            this->data = `malloc(sizeof "T" * this->size);
            for (int i = 0; i < this->size; i++) {
                this->data[i] = data[i];
            }
        }
        T& operator[](int index) {
            return this->data[index];
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this->data, this->size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this->data, this->size, true);
        }
        void _destroy() {
            `free(this->data);
            this->data = nullptr;
            this->size = -1;
        }
        Arr<T, S>& operator=(Arr<T, S> other) {
            if (other.size != this->size) {
                return Arr();
            }
            for (int i = 0; i < other.size; i++) {
                this->data[i] = other.data[i];
            }
            return this;
        }
    }
    Arr proves CoreConcepts::Allocated;
}
#depends(Vector: CoreConcepts)
namespace Vector {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this->data = data;
                this->size = size;
                this->current_index = `ternary(is_end, size, 0);
            }
            bool _atEnd() {
                return this->size <= this->current_index;
            }
            T _next() {
                if (!this->_atEnd()) {
                    return this->data[this->current_index++];
                }
                return this->data[this->size - 1];
            } 
            bool _atStart() {
                return this->current_index <= 0;
            }
            T _prev() {
                if (!this->_atStart()) {
                    return this->data[--this->current_index];
                }
                return this->data[this->current_index];
            }
            void _moveTo(int index) {
                if (index >= this->size) {
                    index = this->size - 1;
                } else if (index < 0) {
                    index = 0;
                }
                this->current_index = index;
            }
        }
    }
    class Vec<T> {
        T* data;
        int size;
        int capacity;
        Vec() {
            this->size = 0;
            this->capacity = 0;
            this->data = nullptr;
        }
        void reserve(int cap) {
            if (cap == 0) {
                `free(this->data);                
                this->data = nullptr;
                this->capacity = 0;
                this->size = 0;
                return;
            }

            T* new_data = `realloc(this->data, sizeof "T" * cap);
            if (new_data == nullptr) {
                return;
            }
            this->capacity = cap;
            if (this->size > this->capacity) {
                this->size = this->capacity;
            }
            this->data = new_data;
        }
        void push(T value) {
            if (this->capacity <= this->size) {
                this->reserve(`ternary(this->capacity == 0, 1, this->capacity * 2));
                if (this->data == nullptr) return;
            }
            this->data[this->size] = value;
            this->size++;
        }
        int length() {
            return this->size;
        }
        void pop() {
            if (this->size > 0) {
                this->size--;
            }
        }
        void shrinkToFit() {
            this->reserve(this->size);
        }
        void operator[]=(T* data, int length) {
            if (this->size != 0) `free(this->data);
            this->capacity = length;
            this->size = length;
            this->data = `malloc((sizeof T) * this->capacity);
            for (int i = 0; i < this->size; i++) {
                this->data[i] = data[i];
            }
        }
        T& operator[](int index) {
            return this->data[index];
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this->data, this->size, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this->data, this->size, true);
        }
        void _destroy() {
            `free(this->data);
            this->data = nullptr;
            this->size = -1;
            this->capacity = -1;
        }
        Vec<T>& operator=(Vec<T> other) {
            if (other.capacity != this->capacity) {
                this->reserve(other.capacity);
            }
            this->size = other.size;
            for (int i = 0; i < other.size; i++) {
                this->data[i] = other.data[i];
            }
            return this;
        }
        bool isEmpty() {
            return this->size == 0;
        }
    }
    Vec proves CoreConcepts::Allocated;
}
#depends(List: CoreConcepts)
namespace List {
    class Node<T> {
        T data;
        Node<T>* next;
        Node<T>* prev;

        Node(T data) {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
    }

    namespace Iterator {
        class It<T> {
            Node<T>* current;

            It(Node<T>* node) {
                this->current = node;
            }

            bool _atEnd() {
                return this->current == nullptr;
            }

            T _next() {
                T value = this->current->data;
                this->current = this->current->next;
                return value;
            }

            bool _atStart() {
                return this->current->prev == nullptr;
            }

            T _prev() {
                T value = this->current->data;
                this->current = this->current->prev;
                return value;
            }
        }
    }

    class List<T> {
        Node<T>* head;
        Node<T>* tail;
        int size;
        List() {
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        }
        private Node<T>* _getNode(int index) {
            if (index < 0 || index >= this->size) {
                return nullptr;
            }
            Node<T>* current;
            if (index < this->size / 2) {
                current = this->head;
                for (int i = 0; i < index; i++) {
                    current = current->next;
                }
            } else {
                current = this->tail;
                for (int i = this->size - 1; i > index; i--) {
                    current = current->prev;
                }
            }
            return current;
        }
        bool isEmpty() {
            return this->size == 0;
        }
        T front() {
            return this->head->data;
        }
        T back() {
            return this->tail->data;
        }
        void pushFront(T value) {
            Node<T>* node = `malloc(sizeof Node<T>);
            *node = Node<T>(value);
            node.next = this->head;
            if (this->head != nullptr) {
                this->head->prev = node;
            } else {
                this->tail = node;
            }
            this->head = node;
            this->size++;
        }
        void pushBack(T value) {
            Node<T>* node = `malloc(sizeof Node<T>);
            *node = Node<T>(value);
            node.prev = this->tail;
            if (this->tail != nullptr) {
                this->tail->next = node;
            } else {
                this->head = node;
            }
            this->tail = node;
            this->size++;
        }
        void popFront() {
            if (this->head == nullptr) {
                return;
            }
            Node<T>* old = this->head;
            this->head = this->head->next;
            if (this->head != nullptr) {
                this->head->prev = nullptr;
            } else {
                this->tail = nullptr;
            }
            `free(old);
            this->size--;
        }
        void popBack() {
            if (this->tail == nullptr) {
                return;
            }
            Node<T>* old = this->tail;
            this->tail = this->tail->prev;
            if (this->tail != nullptr) {
                this->tail->next = nullptr;
            } else {
                this->head = nullptr;
            }
            `free(old);
            this->size--;
        }
        void clear() {
            Node<T>* current = this->head;
            while (current != nullptr) {
                Node<T>* next = current->next;
                `free(current);
                current = next;
            }
            this->head = nullptr;
            this->tail = nullptr;
            this->size = 0;
        }
        bool contains(T value) {
            Node<T>* current = this->head;
            while (current != nullptr) {
                if (current->data == value) {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this->head);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(nullptr);
        }
        void _destroy() {
            this->clear();

            this->head = nullptr;
            this->tail = nullptr;
            this->size = -1;
        }
        T& operator[](int index) {
            Node<T>* node = this->_getNode(index);
            if (node == nullptr) {
                return nullptr;
            }
            return node.data;
        }
        void operator[]=(T* data, int length) {
            while (this->size != 0) this->popBack();
            this->head = nullptr;
            this->tail = nullptr;
            for (int i = 0; i < length; i++) {
                this->pushBack(data[i]);
            }
        }
        List<T>& operator=(List<T> other) {
            this->clear();

            Node<T>* current = other.head;

            while (current != nullptr) {
                this->pushBack(current->data);
                current = current->next;
            }

            return this;
        }
    }
    List proves CoreConcepts::Allocated;
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
            )", result, &(req[0]), &(rem.rem_sec), "~{rax}~{rdi}~{rsi}~{rdx}~{r10}~{rcx}~{r11}");
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
            throw "log: x must be positive";
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
namespace Pair {
    struct Pair<A, B> {
        A first;
        B second;
    }
    Pair<A, B> makePair<A, B>(A first, B second) {
        return Pair<A, B>{first, second};
    }
}
namespace Optional {
    class Option<T> {
        private T data;
        bool has_value;
        Option() {
            this->has_value = false;
        }
        Option(T value) {
            this->data = value;
            this->has_value = true;
        }
        T& value() {
            if (!this->has_value) throw "No value";
            return this->data;
        }
        bool safeGet(T& output) {
            if (!this->has_value) return false;
            output = this->data;
            return true;
        }
        void setValue(T& val) {
            this->data = val;
            this->has_value = true;
        }
        void removeValue() {
            this->has_value = false;
        }
    }
}
namespace Span {
    namespace Iterator {
        class It<T> {
            T* data;
            int size;
            int current_index;
            It(T* data, int size, bool is_end) {
                this->data = data;
                this->size = size;
                this->current_index = `ternary(is_end, size, 0);
            }
            bool _atEnd() {
                return this->size <= this->current_index;
            }
            T _next() {
                if (!this->_atEnd()) {
                    return this->data[this->current_index++];
                }
                return this->data[this->size - 1];
            } 
            bool _atStart() {
                return this->current_index <= 0;
            }
            T _prev() {
                if (!this->_atStart()) {
                    return this->data[--this->current_index];
                }
                return this->data[this->current_index];
            }
            void _moveTo(int index) {
                if (index >= this->size) {
                    index = this->size - 1;
                } else if (index < 0) {
                    index = 0;
                }
                this->current_index = index;
            }
        }
    }
    class Span<T> {
        T* data;
        int length;
        T& operator[](int index) {
            if (index >= this->length) throw "Cannot index past end of a Span";
            return this->data[index];
        }
        Span() {
            this.length = 0;
            this.data = nullptr;
        }
        void operator[]=(T *data, int length) {
            this.length = length;
            this.data = data;
        }
        Iterator::It<T> _begin() {
            return Iterator::It<T>(this->data, this->length, false);
        }
        Iterator::It<T> _end() {
            return Iterator::It<T>(this->data, this->length, true);
        }
    }
}
namespace Encodings {
    namespace Hex {
        const string chars = "0123456789abcdef";
        string encode(string data) {
            string result = "";
            for (int i = 0; i < `len(data); i++) {
                char c = data[i];
                nibble lower = c & 0x0fy;
                nibble upper = (c :> 4y) & 0x0fy;
                result += chars[upper];
                result += chars[lower];
            }
            return result;
        }   
        string decode(string hex) {
            string ascii = "";
            int i = 0;
            int j = 0;
            while (hex[i] != '\0' && hex[i + 1] != '\0') {
                int high = hex[i];
                int low = hex[i + 1];
                high = (high >= 'a') ? (high - 'a' + 10) :  (high >= 'A') ? (high - 'A' + 10) : (high - '0');
                low = (low >= 'a') ? (low - 'a' + 10) : (low >= 'A') ? (low - 'A' + 10) : (low - '0');
                ascii += `to_char((high << 4) | low);
                i += 2;
            }
            return ascii;
        }
    }
    namespace Base64 {
        const string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        string encode(string data) {
            string result = "";
            int i = 0;
            int len = `len(data);
            while (i < len) {
                int b0 = data[i];
                int b1 = (i + 1 < len) ? `to_int(data[i + 1]) : 0;
                int b2 = (i + 2 < len) ? `to_int(data[i + 2]) : 0;
                int idx0 = (b0 :> 2) & 0x3f;
                int idx1 = ((b0 << 4) | (b1 :> 4)) & 0x3f;
                int idx2 = ((b1 << 2) | (b2 :> 6)) & 0x3f;
                int idx3 = b2 & 0x3f;
                result += chars[idx0];
                result += chars[idx1];
                result += (i + 1 < len) ? chars[idx2] : '=';
                result += (i + 2 < len) ? chars[idx3] : '=';
                i += 3;
            }
            return result;
        }
        int charValue(char c) {
            if (c >= 'A' && c <= 'Z') return c - 'A';
            if (c >= 'a' && c <= 'z') return c - 'a' + 26;
            if (c >= '0' && c <= '9') return c - '0' + 52;
            if (c == '+') return 62;
            if (c == '/') return 63;
            return 0;
        }
        string decode(string data) {
            string result = "";
            int i = 0;
            int len = `len(data);
            while (i < len) {
                int v0 = charValue(data[i]);
                int v1 = charValue(data[i + 1]);
                int v2 = (data[i + 2] != '=') ? charValue(data[i + 2]) : 0; // THE HELL IS THIS
                int v3 = (data[i + 3] != '=') ? charValue(data[i + 3]) : 0;
                int b0 = ((v0 << 2) | (v1 :> 4)) & 0xff;
                int b1 = ((v1 << 4) | (v2 :> 2)) & 0xff;
                int b2 = ((v2 << 6) | v3) & 0xff;
                result += `to_char(b0);
                if (data[i + 2] != '=') result += `to_char(b1);
                if (data[i + 3] != '=') result += `to_char(b2);
                i += 4;
            }
            return result;
        }
    }
    namespace URI {
        bool isUnreserved(char c) {
            if (c >= 'A' && c <= 'Z') return true;
            if (c >= 'a' && c <= 'z') return true;
            if (c >= '0' && c <= '9') return true;
            if (c == '-' || c == '_' || c == '.' || c == '~') return true;
            return false;
        }
        string encode(string data) {
            string result = "";
            for (int i = 0; i < `len(data); i++) {
                char c = data[i];
                if (isUnreserved(c)) {
                    result += c;
                } else {
                    result += '%';
                    result += Hex::chars[(c :> 4) & 0x0fb];
                    result += Hex::chars[c & 0x0fb];
                }
            }
            return result;
        }
        string decode(string data) {
            string result = "";
            int i = 0;
            int len = `len(data);
            while (i < len) {
                if (data[i] == '%' && i + 2 < len) {
                    string byteStr = "";
                    byteStr += data[i + 1];
                    byteStr += data[i + 2];
                    string decoded = Hex::decode(byteStr);
                    result += decoded[0];
                    i += 3;
                } else {
                    result += data[i];
                    i += 1;
                }
            }
            return result;
        }
    }
}
/*
namespace Ordered {
}
*/
#depends(Unordered: CoreConcepts)
namespace Unordered {
    concept Hash {
        1_of {
            addr_t hash();
            addr_t hash(Self self);
        }
    }
    class SetNode<T> {
        T value;
        SetNode<T>* next;
    }
    namespace Iterators {
        class SetIt<T> {
            SetNode<T>** buckets;
            int num_buckets;
            int bucket_index;
            SetNode<T>* current;

            SetIt(SetNode<T>** buckets, int num_buckets, bool is_end) {
                this->buckets = buckets;
                this->num_buckets = num_buckets;
                if (is_end) {
                    this->bucket_index = num_buckets;
                    this->current = nullptr;
                } else {
                    this->bucket_index = 0;
                    this->current = nullptr;
                    this->_advanceToNext();
                }
            }
            private void _advanceToNext() {
                while (this->current == nullptr && this->bucket_index < this->num_buckets) {
                    this->current = this->buckets[this->bucket_index];
                    if (this->current == nullptr) this->bucket_index++;
                }
            }
            bool _atEnd() {
                return this->bucket_index >= this->num_buckets;
            }
            T _next() {
                T val = this->current->value;
                this->current = this->current->next;
                if (this->current == nullptr) {
                    this->bucket_index++;
                    this->_advanceToNext();
                }
                return val;
            }
        }
    }
    class Set<T(proves Hash:)> {
        private int num_buckets;
        private int count;
        private SetNode<T>** buckets;
        private int get_Bucket_Index(T item) {
            return item.hash() % this->num_buckets;
        }
        Set() {
            this->num_buckets = 8;
            this->count = 0;
            this->buckets = `malloc((sizeof SetNode<T>*) * this->num_buckets);
            for (int i = 0; i < this->num_buckets; i++) {
                this->buckets[i] = nullptr;
            }
        }
        void operator[]=(T *data, int length) {
            if (num_buckets == 0) this->Set();
            for (int i = 0; i < length; i++) {
                this->add(data[i]);
            }
        }
        bool contains(T item) {
            if (!(CoreConcepts::Eq proved_by T)) {
                `qout("T must prove CoreConcepts::Eq to use contains");
                return false;
            }
            int index = this->get_Bucket_Index(item);
            SetNode<T>* node = this->buckets[index];
            while (node != nullptr) {
                if (node->value == item) return true;
                node = node->next;
            }
            return false;
        }
        private void resize() {
            int old_num_buckets = this->num_buckets;
            SetNode<T>** old_buckets = this->buckets;
            this->num_buckets = old_num_buckets * 2;
            this->buckets = `malloc((sizeof SetNode<T>*) * this->num_buckets);
            for (int i = 0; i < this->num_buckets; i++) {
                this->buckets[i] = nullptr;
            }
            for (int i = 0; i < old_num_buckets; i++) {
                SetNode<T>* node = old_buckets[i];
                while (node != nullptr) {
                    SetNode<T>* next = node->next;
                    int newIndex = node->value.hash() % this->num_buckets;
                    node->next = this->buckets[newIndex];
                    this->buckets[newIndex] = node;
                    node = next;
                }
            }
            `free(old_buckets);
        }
        void add(T item) {
            if (this->contains(item)) return;
            if (this->count + 1 > this->num_buckets * 0.75) {
                this->resize();
            }
            int index = this->get_Bucket_Index(item);
            SetNode<T>* node = `malloc(sizeof SetNode<T>);
            node->value = item;
            node->next = this->buckets[index];
            this->buckets[index] = node;
            this->count++;
        }
        void _destroy() {
            for (int i = 0; i < this->num_buckets; i++) {
                SetNode<T>* node = this->buckets[i];
                while (node != nullptr) {
                    SetNode<T>* next = node->next;
                    `free(node);
                    node = next;
                }
            }
            `free(this->buckets);
        }
        Iterators::SetIt<T> _begin() {
            return Iterators::SetIt<T>(this->buckets, this->num_buckets, false);
        }
        Iterators::SetIt<T> _end() {
            return Iterators::SetIt<T>(this->buckets, this->num_buckets, true);
        }
    }
    Set proves CoreConcepts::Allocated;
    #depends(Unordered: Pair)
    class MapNode<K, V> {
        Pair::Pair<K, V> data;
        MapNode<K, V>* next;
    }
    class Map<K(proves Hash:), V> {
        private int num_buckets;
        private int count;
        private MapNode<K, V>** buckets;
        private int get_Bucket_Index(K key) {
            return key.hash() % this->num_buckets;
        }
        Map() {
            this->num_buckets = 8;
            this->count = 0;
            this->buckets = `malloc((sizeof MapNode<K, V>*) * this->num_buckets);
            for (int i = 0; i < this->num_buckets; i++) {
                this->buckets[i] = nullptr;
            }
        }
        bool containsKey(K key) {
            int index = this->get_Bucket_Index(key);
            MapNode<K, V>* node = this->buckets[index];
            while (node != nullptr) {
                if (node->data.first.equals(key)) return true;
                node = node->next;
            }
            return false;
        }
        bool safeGet(K key, V& output) {
            int index = this->get_Bucket_Index(key);
            MapNode<K, V>* node = this->buckets[index];
            while (node != nullptr) {
                if (node->data.first.equals(key)) {
                    output = node->data.second;
                    return true;
                }
                node = node->next;
            }
            return false;
        }
        void set(K key, V value) {
            int index = this->get_Bucket_Index(key);
            MapNode<K, V>* node = this->buckets[index];
            while (node != nullptr) {
                if (node->data.first.equals(key)) {
                    node->data.second = value;
                    return;
                }
                node = node->next;
            }
            if ((this->count + 1) * 4 > this->num_buckets * 3) {
                this->resize();
                index = this->get_Bucket_Index(key);
            }
            MapNode<K, V>* newNode = `malloc(sizeof MapNode<K, V>);
            newNode->data.first = key;
            newNode->data.second = value;
            newNode->next = this->buckets[index];
            this->buckets[index] = newNode;
            this->count++;
        }
        private void resize() {
            int old_num_buckets = this->num_buckets;
            MapNode<K, V>** old_buckets = this->buckets;
            this->num_buckets = old_num_buckets * 2;
            this->buckets = `malloc((sizeof MapNode<K, V>*) * this->num_buckets);
            for (int i = 0; i < this->num_buckets; i++) {
                this->buckets[i] = nullptr;
            }
            for (int i = 0; i < old_num_buckets; i++) {
                MapNode<K, V>* node = old_buckets[i];
                while (node != nullptr) {
                    MapNode<K, V>* next = node->next;
                    int newIndex = node->data.first.hash() % this->num_buckets;
                    node->next = this->buckets[newIndex];
                    this->buckets[newIndex] = node;
                    node = next;
                }
            }
            `free(old_buckets);
        }
        void _destroy() {
            for (int i = 0; i < this->num_buckets; i++) {
                MapNode<K, V>* node = this->buckets[i];
                while (node != nullptr) {
                    MapNode<K, V>* next = node->next;
                    `free(node);
                    node = next;
                }
            }
            `free(this->buckets);
        }
        void operator[]=(Pair::Pair<K, V> *data, int length) {
            if (this->num_buckets == 0) this->Map(); 
            for (int i = 0; i < length; i++) {
                this->set(data[i].first, data[i].second);
            }
        }
        V& operator[](K key) {
            int index = this->getBucketIndex(key);
            MapNode<K, V>* node = this->buckets[index];
            while (node != nullptr) {
                if (node->data.first.equals(key)) return node->data.second;
                node = node->next;
            }
            throw "Key not found";
        }
    }
    Map proves CoreConcepts::Allocated;
}
