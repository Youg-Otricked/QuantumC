class Person {
    string name;
    int age;
    
    Person(string n, int a) {
        this.name = n;
        this.age = a;
    }
    
    string getName() {
        return this.name;
    }
    
    int getAge() {
        return this.age;
    }
}

int main() {
    Person p = Person("Alice", 30);
    
    // Test .has() for fields
    if (p.has("name")) {
        std::qout << "Person has 'name' field\n";
    }
    
    if (p.has("age")) {
        std::qout << "Person has 'age' field\n";
    }
    
    if (!p.has("email")) {
        std::qout << "Person does NOT have 'email' field\n";
    }
    
    // Test .has_method() for methods
    if (p.has_method("getName")) {
        std::qout << "Person has 'getName' method\n";
    }
    
    if (p.has_method("getAge")) {
        std::qout << "Person has 'getAge' method\n";
    }
    
    if (!p.has_method("setEmail")) {
        std::qout << "Person does NOT have 'setEmail' method\n";
    }
    
    // Dynamic field access based on .has()
    if (p.has("name")) {
        string n = p.getName();
        std::qout << "Name: " << n << "\n";
    }
    
    return 0;
}