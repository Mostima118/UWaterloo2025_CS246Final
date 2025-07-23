module goblin;
import <string>;

using namespace std;

Goblin::Goblin() : PlayerCharacter{110, 110, 15, 20, '@', "Player", "Goblin"} {}

void Goblin::attackEffect(unique_ptr<Character> target) {
    PlayerCharacter::attackEffect(target);
    if (target == nullptr) {
        return;
    }
    
    if (target.getHP() <= 0) { // target died from this attack
        addGold(5);
    }
}
