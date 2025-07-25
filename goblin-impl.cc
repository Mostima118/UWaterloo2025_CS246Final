module goblin;
import <string>;

using namespace std;

Goblin::Goblin(int hp, int maxHP, int atk, int def, char mapSymbol, string type, string race) : PlayerCharacter{hp, maxHP, atk, def, mapSymbol, type, race} {}

void Goblin::attackEffect(unique_ptr<Character> target) {
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
    
    if (target->getHP() <= 0) { // target died from this attack
        addGold(5);
    }
}
