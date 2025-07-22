module potions;
import player;

// Restore Health
RestoreHealthPotion::RestoreHealthPotion(int row, int col)
    : Potion(row, col, PotionType::RH) {}

void RestoreHealthPotion::applyTo(Player& player) {
    player.modifyHP(+10);  // example: restore 10 HP
}

char RestoreHealthPotion::getSymbol() const {
    return '0';
}

// Boost Atk
BoostAtkPotion::BoostAtkPotion(int row, int col)
    : Potion(row, col, PotionType::BA) {}

void BoostAtkPotion::applyTo(Player& player) {
    player.modifyAtk(+5);  // example: boost attack by 5
}

char BoostAtkPotion::getSymbol() const {
    return '1';
}

// Boost Def
BoostDefPotion::BoostDefPotion(int row, int col)
    : Potion(row, col, PotionType::BD) {}

void BoostDefPotion::applyTo(Player& player) {
    player.modifyDef(+5);  // example: boost defense by 5
}

char BoostDefPotion::getSymbol() const {
    return '2';
}

// Poison Health
PoisonHealthPotion::PoisonHealthPotion(int row, int col)
    : Potion(row, col, PotionType::PH) {}

void PoisonHealthPotion::applyTo(Player& player) {
    player.modifyHP(-10);  // example: poison, lose 10 HP
}

char PoisonHealthPotion::getSymbol() const {
    return '3';
}

// Wound Atk
WoundAtkPotion::WoundAtkPotion(int row, int col)
    : Potion(row, col, PotionType::WA) {}

void WoundAtkPotion::applyTo(Player& player) {
    player.modifyAtk(-5);  // example: reduce attack by 5
}

char WoundAtkPotion::getSymbol() const {
    return '4';
}

// Wound Def
WoundDefPotion::WoundDefPotion(int row, int col)
    : Potion(row, col, PotionType::WD) {}

void WoundDefPotion::applyTo(Player& player) {
    player.modifyDef(-5);  // example: reduce defense by 5
}

char WoundDefPotion::getSymbol() const {
    return '5';
}
