module enemy;
import <algorithm>;
import <random>;
import <utility>;
import <cstdlib>;
import <ctime>;

using namespace std;

bool Enemy::hostile = false;


Enemy::Enemy(int hp, int atk, int def, char mapSymbol, string type) : 
    Character{hp, hp, atk, def, mapSymbol, type}, hoardPos{Position()} {}

// base behaviour for non human/merchant enemies - randomly add either 1 or 2 gold to player total
int Enemy::dropGold() const {
    srand(time(0));
    int pileSize = rand() % 2;
    if (pileSize == 0) {
        return 1;
    }
    else {
        return 2;
    }
}

int Enemy::attackEffect(Character* target) {
    if (target == nullptr) {
        return 1;
    }
    
    //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
    //srand(time(0));
    int miss = rand() % 2;
    if (miss == 0) { // only hits 50% of the time
        int damage = target->calculateDamage(atk);
        target->setHP(target->getHP() - damage);
        return 0;
    }
    return 1;
}

bool Enemy::isHostile() { 
    return hostile; 
}

void Enemy::setHostile(bool newHostile) { 
    hostile = newHostile; 
}

void Enemy::setHoardPos(Position pos) {
    hoardPos = pos;
}

Position Enemy::getHoardPos() const {
    return hoardPos;
}
