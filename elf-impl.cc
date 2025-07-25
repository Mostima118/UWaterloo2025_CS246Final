module elf;
import <ctime>;
import <cstdlib>;
using namespace std;

Elf::Elf(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

void Elf::attackEffect(Character* target) {
    if (target == nullptr) {
        return;
    }
    
    srand(time(0));
    int miss = rand() % 2;
    if (miss == 0) { // only hits 50% of the time
        int damage = target->calculateDamage(atk);
        target->setHP(target->getHP() - damage);
    }

    if (target->getType() != "Drow") {
        srand(time(0));
        int miss = rand() % 2;
        if (miss == 0) { // only hits 50% of the time
            int damage = target->calculateDamage(atk);
            target->setHP(target->getHP() - damage);
        }
    }
}
