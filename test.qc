// Single return (should still work)
int add(int a, int b) {
    return a + b;
}

// Multi-return function
int, string get_user() {
    return 42, "Alice";
}

// Multi-return with 3 values
int, float, bool get_data() {
    return 100, 3.14f, true;
}

// Multi-return with default args
int, string greet(string name = "World") {
    return 200, "Hello, " + name;
}

int main() {
    // Test single return
    int sum = add(5, 10);
    std::qout << "5 + 10 = " << sum << '\n';
    
    // Test multi-return
    int id, string name = get_user();
    std::qout << "User ID: " << id << '\n';
    std::qout << "User Name: " << name << '\n';
    
    // Test 3-value return
    int code, float pi, bool flag = get_data();
    std::qout << "Code: " << code << '\n';
    std::qout << "Pi: " << pi << '\n';
    std::qout << "Flag: " << flag << '\n';
    
    // Test with default args
    int status1, string msg1 = greet();
    std::qout << status1 << ": " << msg1 << '\n';
    
    int status2, string msg2 = greet("Quantum C");
    std::qout << status2 << ": " << msg2 << '\n';
    
    return 0;
}