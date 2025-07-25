module boostatkpotion;

import potion;

// BoostAtkPotion
BoostAtkPotion::BoostAtkPotion(int x, int y) : Potion(x, y, PotionType::BA) {}
char BoostAtkPotion::getType() { return '1'; }
std::string BoostAtkPotion::use() { return "BA"; }
bool BoostAtkPotion::isDragonHoard() { return false; }
// ADD THIS:
char BoostAtkPotion::getSymbol() const { return 'P'; }