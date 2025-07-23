module drow;
import <string>;

using namespace std;

Drow::Drow() : PlayerCharacter{150, 150, 25, 15, '@', "Player", "Drow"} {}

void Drow::usePotion(string potionType) {
    if (potionType == "RH") {
        setHP(hp + 15);
    }
    else if (potionType = "BA") {
        setAtk(8);
    }
    else if (potionType = "BD") {
        setDef(8);
    }
    else if (potionType = "PH") {
        setHP(hp - 15);
    }
    else if (potionType = "WA") {
        setAtk(-8);
    }
    else if (potionType = "WD") {
        setDef(-8);
    }
}
