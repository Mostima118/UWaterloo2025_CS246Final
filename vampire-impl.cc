module vampire;
import <string>;

using namespace std;
// max hp of 0 meaning no max hp
Vampire::Vampire(int hp, int maxHP, int atk, int def, char mapSymbol, string type, string race) : PlayerCharacter{hp, maxHP, atk, def, mapSymbol, type, race} {}

void Vampire::attackEffect(Character* target) {
    if (target == nullptr) {
        return;
    }

    int damage = target->calculateDamage(atk);
    if (target->getType() == "Halfling") { // if attacking a halfling might miss
        srand(time(0));
        int miss = rand() % 2;
        if (miss == 0) {
            return;
        }
    }
    target->setHP(target->getHP() - damage);
    
    if (target->getType() == "Dwarf") {
        setHP(getHP() - 5);
    }
    else {
        setHP(getHP() + 5);
    }
}
