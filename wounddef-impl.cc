module wounddefpotion;

import potion;

// WoundDefPotion
WoundDefPotion::WoundDefPotion(int x, int y) : Potion(x, y, PotionType::WD) {}
char WoundDefPotion::getType() { return '5'; }
std::string WoundDefPotion::use() { return "WD"; }
bool WoundDefPotion::isDragonHoard() { return false; }
// ADD THIS:
char WoundDefPotion::getSymbol() const { return 'P'; }