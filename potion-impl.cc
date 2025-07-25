module potion;

import <string>;
import player;

Potion::Potion(int x, int y, PotionType type) : Item(x, y), potionType{type} {}

PotionType Potion::getPotionType() const { return potionType; }

bool Potion::isSeen() { 
    switch(potionType) {
        case RH : return seen[0];
        case BA : return seen[1];
        case BD : return seen[2];
        case PH : return seen[3];
        case WA : return seen[4];
        case WD : return seen[5];
    }
    return false;
}


void Potion::See() { 
    switch(potionType) {
        case RH : seen[0] = true;
        case BA : seen[1] = true;
        case BD : seen[2] = true;
        case PH : seen[3] = true;
        case WA : seen[4] = true;
        case WD : seen[5] = true;
    }
}

char Potion::getSymbol() const { return 'P'; }

bool Potion::isPotion() const { return true; }

// RestoreHealthPotion
RestoreHealthPotion::RestoreHealthPotion(int x, int y) : Potion(x, y, PotionType::RH) {}
char RestoreHealthPotion::getType() const { return '0'; }
std::string RestoreHealthPotion::use() { return "RH"; }

// BoostAtkPotion
BoostAtkPotion::BoostAtkPotion(int x, int y) : Potion(x, y, PotionType::BA) {}
char BoostAtkPotion::getType() const { return '1'; }
std::string BoostAtkPotion::use() { return "BA"; }

// BoostDefPotion
BoostDefPotion::BoostDefPotion(int x, int y) : Potion(x, y, PotionType::BD) {}
char BoostDefPotion::getType() const { return '2'; }
std::string BoostDefPotion::use() { return "BD"; }

// PoisonHealthPotion
PoisonHealthPotion::PoisonHealthPotion(int x, int y) : Potion(x, y, PotionType::PH) {}
char PoisonHealthPotion::getType() const { return '3'; }
std::string PoisonHealthPotion::use() { return "PH"; }

// WoundAtkPotion
WoundAtkPotion::WoundAtkPotion(int x, int y) : Potion(x, y, PotionType::WA) {}
char WoundAtkPotion::getType() const { return '4'; }
std::string WoundAtkPotion::use() { return "WA"; }

// WoundDefPotion
WoundDefPotion::WoundDefPotion(int x, int y) : Potion(x, y, PotionType::WD) {}
char WoundDefPotion::getType() const { return '5'; }
std::string WoundDefPotion::use() { return "WD"; }
