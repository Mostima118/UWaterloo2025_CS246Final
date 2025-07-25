module poisonhealthpotion;

import potion;

// PoisonHealthPotion
PoisonHealthPotion::PoisonHealthPotion(int x, int y) : Potion(x, y, PotionType::PH) {}
char PoisonHealthPotion::getType() { return '3'; }
std::string PoisonHealthPotion::use() { return "PH"; }
bool PoisonHealthPotion::isDragonHoard() { return false; }
// ADD THIS:
char PoisonHealthPotion::getSymbol() const { return 'P'; }