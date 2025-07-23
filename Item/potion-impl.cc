module potion;

import player;

Potion::Potion(int x, int y, PotionType type) : Item(x, y), potionType{type}, identified{false} {}

PotionType Potion::getPotionType() const { return potionType; }
bool Potion::isIdentified() const { return identified; }
void Potion::identify() { identified = true; }

char Potion::getSymbol() const { return 'P'; }

bool Potion::isPotion() const { return true; }

// RestoreHealthPotion
RestoreHealthPotion::RestoreHealthPotion(int x, int y) : Potion(x, y, PotionType::RH) {}
char RestoreHealthPotion::getType() const { return '0'; }
char RestoreHealthPotion::use() { return 'RH'; }

// BoostAtkPotion
BoostAtkPotion::BoostAtkPotion(int x, int y) : Potion(x, y, PotionType::BA) {}
char BoostAtkPotion::getType() const { return '1'; }
char BoostAtkPotion::use() { return 'BA'; }

// BoostDefPotion
BoostDefPotion::BoostDefPotion(int x, int y) : Potion(x, y, PotionType::BD) {}
char BoostDefPotion::getType() const { return '2'; }
char BoostDefPotion::use() { return 'BD'; }

// PoisonHealthPotion
PoisonHealthPotion::PoisonHealthPotion(int x, int y) : Potion(x, y, PotionType::PH) {}
char PoisonHealthPotion::getType() const { return '3'; }
char PoisonHealthPotion::use() { return 'PH'; }

// WoundAtkPotion
WoundAtkPotion::WoundAtkPotion(int x, int y) : Potion(x, y, PotionType::WA) {}
char WoundAtkPotion::getType() const { return '4'; }
char WoundAtkPotion::use() { return 'WA'; }

// WoundDefPotion
WoundDefPotion::WoundDefPotion(int x, int y) : Potion(x, y, PotionType::WD) {}
char WoundDefPotion::getType() const { return '5'; }
char WoundDefPotion::use() { return 'WD'; }
