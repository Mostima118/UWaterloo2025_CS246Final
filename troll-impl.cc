module troll;
import <string>;

Troll::Troll() : PlayerCharacter{120, 120, 25, 15, '@', "Player", "Troll"} {}

void Troll::specialAbility() {
    setHP(getHP() + 5);
    if (getHP() > getMaxHP()) {
        setHP(getMaxHP());
    }
}
