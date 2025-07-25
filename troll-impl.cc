module troll;
import <string>;

using namespace std;

Troll::Troll(int hp, int maxHP, int atk, int def, char mapSymbol, string type, string race) : PlayerCharacter{hp, maxHP, atk, def, mapSymbol, type, race} {}

void Troll::specialAbility() {
    setHP(getHP() + 5);
    if (getHP() > getMaxHP()) {
        setHP(getMaxHP());
    }
}
