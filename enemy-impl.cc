module enemy;
import <algorithm>;
import <random>;
import <utility>;
import <cstdlib>;
import <ctime>;

using namespace std;

Enemy::Enemy(int hp, int atk, int def, char mapSymbol, string type) : 
    Character{hp, hp, atk, def, mapSymbol, type} {}

// base behaviour for non human/merchant enemies - randomly add either 1 or 2 gold to player total
int Enemy::dropGold() const {
    srand(time(0));
    int pileSize = rand() % 2;
    if (pileSize = 0) {
        return 1;
    }
    else {
        return 2;
    }
}

void Enemy::attackEffect(unique_ptr<Character> target) {
    if (target == nullptr) {
        return;
    }
    
    srand(time(0));
    int miss = rand() % 2;
    if (miss == 0) { // only hits 50% of the time
        int damage = target->calculateDamage(atk);
        target->setHP(target->getHP() - damage);
    }
}
