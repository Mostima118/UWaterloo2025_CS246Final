module restorehealthpotion;

import potion;

// RestoreHealthPotion
RestoreHealthPotion::RestoreHealthPotion(int x, int y) : Potion(x, y, PotionType::RH) {}
char RestoreHealthPotion::getType() { return '0'; }
std::string RestoreHealthPotion::use() { return "RH"; }
bool RestoreHealthPotion::isDragonHoard() { return false; }
// ADD THIS:
char RestoreHealthPotion::getSymbol() const { return 'P'; }
