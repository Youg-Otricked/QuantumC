class Enemy {
    int hp;

    public Enemy(int hp) {
        this.hp = hp;
    }

    public void damage(int amount) {
        this.hp -= amount;
    }
    protected void repr() {
        println(this.hp);
    }
    public int getHp() {
        return this.hp;
    }
}

class Boss : Enemy {
    int rage;

    public Boss(int hp, int rage) {
        this.rage = rage;
        this.hp = hp * 10;
    }

    public void enrage() {
        this.rage += 10;
    }
}
class FinalBoss : Boss {
    int lackeys;

    public FinalBoss(int lackeys, int hp, int rage) {
        this.rage = rage;
        this.hp = hp * 10;
        this.lackeys = lackeys;
    }

    public void pnt() {
        this.repr();
    }
    public void kill_lackey() {
        this.lackeys -= 1;
    }
    public void enrage() {
        this.rage += 20;
    }
}


int main() {
    Boss b = Boss(100, 0);
    b.damage(30);
    println(b.getHp());
    b.enrage();
    FinalBoss fb = FinalBoss(1000, 100, 10);
    fb.pnt();
    fb.enrage();
    println(fb.rage);
    return 0;
}