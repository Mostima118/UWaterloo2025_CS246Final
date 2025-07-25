module playercharacter;
import <string>;
import <cstdlib>;
import <ctime>;

using namespace std;

PlayerCharacter::PlayerCharacter(int hp, int maxHP, int atk, int def, char mapSymbol, string type, string race) : 
    Character{hp, maxHP, atk, def, mapSymbol, type}, gold{0}, defaultAtk{atk}, defaultDef{def}, race{race} {}


int PlayerCharacter::getGold() const {
    return gold;
}

void PlayerCharacter::addGold(int amount) {
    gold += amount;
}


string PlayerCharacter::getRace() const {
    return race;
}

void PlayerCharacter::setAtk(int atkChange) {
    atk += atkChange;
    if (atk < 0) {
        atk = 0;
    }
}

void PlayerCharacter::setDef(int defChange) {
    def += defChange;
    if (def < 0) {
        def = 0;
    }
}

void PlayerCharacter::usePotion(string potionType) {
    if (potionType == "null") {
        return;
    }
    else if (potionType == "RH") {
        setHP(hp + 10);
    }
    else if (potionType == "BA") {
        setAtk(5);
    }
    else if (potionType == "BD") {
        setDef(5);
    }
    else if (potionType == "PH") {
        setHP(hp - 10);
    }
    else if (potionType == "WA") {
        setAtk(-5);
    }
    else if (potionType == "WD") {
        setDef(-5);
    }
}

void PlayerCharacter::resetPotions() {
    atk = defaultAtk;
    def = defaultDef;
}


int PlayerCharacter::calculateScore() const {
    return gold; // default, overriden by shade subclass
}


// default behaviour, may be overriden by subclasses
int PlayerCharacter::attackEffect(Character* target) {
    if (target == nullptr) {
        return 1;
    }

    int damage = target->calculateDamage(atk);
    if (target->getType() == "Halfling") { // if attacking a halfling might miss
        //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
        //srand(time(0));
        int miss = rand() % 2;
        if (miss == 0) {
            return 1;
        }
    }
    target->setHP(target->getHP() - damage);
    return 0;
}


//void PlayerCharacter::specialAbility() {}
