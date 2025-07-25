module shade;
import <string>;

using namespace std;

Shade::Shade(int hp, int maxHP, int atk, int def, char mapSymbol, string type, string race) : PlayerCharacter{hp, maxHP, atk, def, mapSymbol, type, race} {}


int Shade::calculateScore() const {
    return static_cast<int>(getGold() * 1.5);
}

