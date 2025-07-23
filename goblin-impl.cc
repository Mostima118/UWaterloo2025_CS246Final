module goblin;
import <string>;

Goblin::Goblin() : PlayerCharacter{110, 110, 15, 20, '@', "Player", "Goblin"} {}

void Goblin::attackEffect(Character &target) {
    PlayerCharacter::attackEffect(target);
    if (target.getHP() <= 0) { // target died from this attack
        addGold(5);
    }
}
