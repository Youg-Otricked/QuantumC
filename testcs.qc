// Test 1: Basic namespace
namespace math {
    int add(int a, int b) {
        return a + b;
    }
    
    int multiply(int x, int y) {
        return x * y;
    }
}

// Test 2: Nested namespaces
namespace graphics {
    namespace shapes {
        class Circle {
            int radius;
            
            Circle(int r) {
                this.radius = r;
            }
            
            int getArea() {
                return 3 * this.radius * this.radius;
            }
        }
        
        class Rectangle {
            int width;
            int height;
            
            Rectangle(int w, int h) {
                this.width = w;
                this.height = h;
            }
            
            int getArea() {
                return this.width * this.height;
            }
        }
    }
    
    namespace colors {
        enum Color {
            RED = 255;
            GREEN = 65280;
            BLUE = 16711680;
        }
    }
}

// Test 3: Namespace with enums and unions
namespace data {
    enum Status {
        OK = 0;
        ERROR = 1;
        PENDING = 2;
    }
    
    type Result = int | string;
    
    struct Response {
        Status status;
        Result result;
    }
}

// Test 4: Multiple namespaces with same names (different scopes)
namespace game {
    class Player {
        int health;
        int score;
        
        Player(int h, int s) {
            this.health = h;
            this.score = s;
        }
        
        void takeDamage(int damage) {
            this.health -= damage;
        }
    }
    
    int calculateScore(int kills, int deaths) {
        return kills * 10 - deaths * 5;
    }
}

namespace network {
    class Player {
        string username;
        int ping;
        
        Player(string name, int p) {
            this.username = name;
            this.ping = p;
        }
        
        string getUsername() {
            return this.username;
        }
    }
}

// Test 5: Namespace resolution from inside namespace
namespace physics {
    int GRAVITY = 10;
    
    class Body {
        int mass;
        int velocity;
        
        Body(int m) {
            this.mass = m;
            this.velocity = 0;
        }
        
        void applyGravity() {
            this.velocity += GRAVITY;
        }
        
        int getMomentum() {
            return this.mass * this.velocity;
        }
    }
    
    int calculateForce(int mass, int acceleration) {
        return mass * acceleration;
    }
}

// Test 6: Cross-namespace usage
namespace utils {
    int square(int x) {
        return x * x;
    }
    
    int cube(int x) {
        return x * x * x;
    }
}

namespace geometry {
    // Using function from another namespace
    int sphereVolume(int radius) {
        int r_cubed = utils::cube(radius);
        return 4 * r_cubed / 3;
    }
}

// Test 7: Namespace with inheritance
namespace entities {
    class Entity {
        int x;
        int y;
        
        Entity(int px, int py) {
            this.x = px;
            this.y = py;
        }
        
        void move(int dx, int dy) {
            this.x = this.x + dx;
            this.y = this.y + dy;
        }
    }
    
    class Monster : Entity {
        int damage;
        
        Monster(int px, int py, int d) {
            Entity(px, py);
            this.damage = d;
        }
        
        int getDamage() {
            return this.damage;
        }
    }
}

// Test 8: Deeply nested namespaces
namespace company {
    namespace department {
        namespace team {
            class Employee {
                string name;
                int salary;
                
                Employee(string n, int s) {
                    this.name = n;
                    this.salary = s;
                }
                
                string getName() {
                    return this.name;
                }
            }
            
            int teamSize = 5;
        }
    }
}

// Test 9: Global scope access from namespace
int GLOBAL_CONSTANT = 100;

namespace scoped {
    int localValue = 50;
    
    int getTotal() {
        return GLOBAL_CONSTANT + localValue;
    }
}

// Test 10: Namespace with arrays and lists
namespace collections {
    int[] getNumbers() {
        return [1, 2, 3, 4, 5];
    }
    
    list<int> createList() {
        list<int> nums = [10, 20, 30];
        return nums;
    }
}

// MAIN TEST FUNCTION
int main() {
    // Test basic namespace functions
    int sum = math::add(5, 3);
    int product = math::multiply(4, 7);
    std::qout << "Math: " << sum << ", " << product << '\n';
    
    // Test nested namespaces with classes
    graphics::shapes::Circle c = graphics::shapes::Circle(5);
    int area = c.getArea();
    std::qout << "Circle area: " << area << '\n';
    
    graphics::shapes::Rectangle r = graphics::shapes::Rectangle(4, 6);
    int rectArea = r.getArea();
    std::qout << "Rectangle area: " << rectArea << '\n';
    
    // Test enum in namespace
    graphics::colors::Color red = graphics::colors::Color.RED;
    std::qout << "Red color value: " << red << '\n';
    
    // Test union in namespace
    data::Result res = 42;
    data::Status status = data::Status.OK;
    std::qout << "Status: " << status << '\n';
    
    // Test multiple namespaces with same class name
    game::Player gamePlayer = game::Player(100, 0);
    gamePlayer.takeDamage(20);
    
    network::Player netPlayer = network::Player("Alice", 50);
    string username = netPlayer.getUsername();
    std::qout << "Network player: " << username << '\n';
    
    // Test physics namespace
    physics::Body body = physics::Body(10);
    body.applyGravity();
    int momentum = body.getMomentum();
    std::qout << "Momentum: " << momentum << '\n';
    
    int force = physics::calculateForce(5, 10);
    std::qout << "Force: " << force << '\n';
    
    // Test cross-namespace usage
    int volume = geometry::sphereVolume(3);
    std::qout << "Sphere volume: " << volume << '\n';
    
    // Test inheritance in namespace
    entities::Monster monster = entities::Monster(10, 20, 15);
    monster.move(5, 5);
    int dmg = monster.getDamage();
    std::qout << "Monster damage: " << dmg << '\n';
    
    // Test deeply nested namespace
    company::department::team::Employee emp = 
        company::department::team::Employee("Bob", 50000);
    string empName = emp.getName();
    std::qout << "Employee: " << empName << '\n';
    
    // Test global scope access
    int total = scoped::getTotal();
    std::qout << "Total: " << total << '\n';
    
    // Test collections in namespace
    int[] numbers = collections::getNumbers();
    std::qout << "First number: " << numbers[0] << '\n';
    
    list<int> myList = collections::createList();
    std::qout << "List length: " << myList.length << '\n';
    
    return 0;
}