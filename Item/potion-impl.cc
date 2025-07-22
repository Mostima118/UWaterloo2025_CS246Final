module potion;

import player;

Potion::Potion(int r, int c, PotionType type) : Item(r, c), potionType{type}, identified{false} {}

PotionType Potion::getPotionType() const { return potionType; }
bool Potion::isIdentified() const { return identified; }
void Potion::identify() { identified = true; }

bool Potion::isPotion() const { return true; }

// RestoreHealthPotion
RestoreHealthPotion::RestoreHealthPotion(int r, int c) : Potion(r, c, PotionType::RH) {}
char RestoreHealthPotion::getSymbol() const { return '0'; }
void RestoreHealthPotion::use(class Player& player) { /* implement will be based on the player functions */ }
//////////////////////////////// Example implementation /////////////////////////////////
/* void RestoreHealthPotion::use(Player& player) {
    player.modifyHP(+10);
}*/

// BoostAtkPotion
BoostAtkPotion::BoostAtkPotion(int r, int c) : Potion(r, c, PotionType::BA) {}
char BoostAtkPotion::getSymbol() const { return '1'; }
void BoostAtkPotion::use(class Player& player) { /* implement will be based on the player functions */ }

// BoostDefPotion
BoostDefPotion::BoostDefPotion(int r, int c) : Potion(r, c, PotionType::BD) {}
char BoostDefPotion::getSymbol() const { return '2'; }
void BoostDefPotion::use(class Player& player) { /* implement will be based on the player functions */ }

// PoisonHealthPotion
PoisonHealthPotion::PoisonHealthPotion(int r, int c) : Potion(r, c, PotionType::PH) {}
char PoisonHealthPotion::getSymbol() const { return '3'; }
void PoisonHealthPotion::use(class Player& player) { /* implement will be based on the player functions */ }

// WoundAtkPotion
WoundAtkPotion::WoundAtkPotion(int r, int c) : Potion(r, c, PotionType::WA) {}
char WoundAtkPotion::getSymbol() const { return '4'; }
void WoundAtkPotion::use(class Player& player) { /* implement will be based on the player functions */ }

// WoundDefPotion
WoundDefPotion::WoundDefPotion(int r, int c) : Potion(r, c, PotionType::WD) {}
char WoundDefPotion::getSymbol() const { return '5'; }
void WoundDefPotion::use(class Player& player) { /* implement will be based on the player functions */ }
