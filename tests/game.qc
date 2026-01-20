namespace Exported {
    int globalScore = 0;
    
    void incrementScore(int amount) {
        globalScore += amount;
    }
}

namespace game {
    struct Player {
        int hp;
        int mp;
    }
    
    Player createPlayer(int level) {
        Player p = { 0, 0 };
        p.hp = level * 10;
        p.mp = level * 5;
        return p;
    }
    
    int calculateDamage(int base, int multiplier) {
        return base * multiplier;
    }
}