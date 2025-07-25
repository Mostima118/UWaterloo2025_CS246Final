module character;
import <cmath>;

using namespace std;

Character::Character(int hp, int maxHP, int atk, int def, char mapSymbol, string type) : 
    hp{hp}, maxHP{maxHP}, atk{atk}, def{def}, mapSymbol{mapSymbol}, type{type}, pos{0, 0} {}

int Character::getHP() const {
    return hp;
}
int Character::getMaxHP() const {
    return maxHP;
}
int Character::getAtk() const {
    return atk;
}
int Character::getDef() const {
    return def;
}
char Character::getSymbol() const {
    return mapSymbol;
}
string Character::getType() const {
    return type;
}
Position Character::getPosition() const {
    return Position {pos.x, pos.y};
}

bool Character::isAlive() const {
    return hp > 0;
}

void Character::setHP(int newHP) {
    if (newHP < 0) {
        hp = 0;
    }
    else if (newHP > maxHP) {
        hp = maxHP;
    }
    else {
        hp = newHP;
    }
}

// no need check because command interpreter should ensure a move is valid
void Character::setPosition(int newX, int newY) {
    pos.x = newX;
    pos.y = newY;
}

// calculate damage
int Character::calculateDamage(int attackerAtk) const {
    return static_cast<int>(std::ceil((100.0 / (100 + def)) * attackerAtk));
}


// Default implementations

void Character::specialAbility() {}
int Character::attackEffect(Character* target) {return 0;}
//void Character::defenseEffect(Character &attacker) {}

