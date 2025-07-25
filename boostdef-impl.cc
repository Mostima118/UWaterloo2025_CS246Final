module boostdefpotion;

import potion;

// BoostDefPotion
BoostDefPotion::BoostDefPotion(int x, int y) : Potion(x, y, PotionType::BD) {}
char BoostDefPotion::getType() { return '2'; }
std::string BoostDefPotion::use() { return "BD"; }
bool BoostDefPotion::isDragonHoard() { return false; }
// ADD THIS:
char BoostDefPotion::getSymbol() const { return 'P'; }
