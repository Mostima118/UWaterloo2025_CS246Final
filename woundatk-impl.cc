module woundatkpotion;

import potion;

// WoundAtkPotion
WoundAtkPotion::WoundAtkPotion(int x, int y) : Potion(x, y, PotionType::WA) {}
char WoundAtkPotion::getType() { return '4'; }
std::string WoundAtkPotion::use() { return "WA"; }
bool WoundAtkPotion::isDragonHoard() { return false; }
// ADD THIS:
char WoundAtkPotion::getSymbol() const { return 'P'; }