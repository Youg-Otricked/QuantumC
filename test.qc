// @print-ast
// @print-tokens

int main() {
    // struct definitions
    struct Vec2 {
        float x;
        float y;
    };

    struct Inventory {
        int[] bag;     
        string slots[];
    };

    struct Player {
        string name;
        int hp;
        Vec2 pos;
        Inventory inv;
    };

    Player p = {
        "Alice",
        100,   
        {1.0f, 2.0f},
        { [1, 2, 3], ["head"] }
    };

    println(p.name);
    println(p.hp);
    println(p.pos.x);
    println(p.pos.y);
    println(p.inv.bag.length);
    println(p.inv.slots[0]);

    Player q = p;
    q.name = "Bob";
    q.hp = 50;
    q.pos.x = 9.0f;

    println(p.name);
    println(p.hp);
    println(p.pos.x);

    println(q.name);
    println(q.hp);
    println(q.pos.x); 

    p.inv.bag.push(4);
    println(p.inv.bag.length);

    return 0;
}