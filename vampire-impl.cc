module vampire;
import <string>;

using namespace std;
// max hp of 0 meaning no max hp
Vampire::Vampire() : PlayerCharacter{50, 0, 25, 25, '@', "Player", "Vampire"} {}

void Vampire::attackEffect(unique_ptr<Character> target) {
    PlayerCharacter::attackEffect(target);
    if (target == nullptr) {
        return;
    }
    
    if (target->getType() == "Dwarf") {
        setHP(getHP() - 5);
    }
    else {
        setHP(getHP() + 5);
    }
}
