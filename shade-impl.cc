module shade;
import <string>;

Shade::Shade() : PlayerCharacter{125, 125, 25, 25, '@', "Player", "Shade"} {}


int Shade::calculateScore() const {
    return static_cast<int>(getGold() * 1.5);
}

