module potion;

import <string>;

Potion::Potion(int x, int y, PotionType type) : Item(x, y), potionType{type} {}

bool Potion::seen[6] = {false, false, false, false, false, false};

PotionType Potion::getPotionType() const { return potionType; }

bool Potion::isSeen() { 
    switch(potionType) {
        case PotionType::RH : return seen[0];
        case PotionType::BA : return seen[1];
        case PotionType::BD : return seen[2];
        case PotionType::PH : return seen[3];
        case PotionType::WA : return seen[4];
        case PotionType::WD : return seen[5];
    }
    return false;
}


void Potion::See() { 
    switch(potionType) {
        case PotionType::RH : seen[0] = true;
        case PotionType::BA : seen[1] = true;
        case PotionType::BD : seen[2] = true;
        case PotionType::PH : seen[3] = true;
        case PotionType::WA : seen[4] = true;
        case PotionType::WD : seen[5] = true;
    }
}

char Potion::getSymbol() const { return 'P'; }

int Potion::getValue() { return 0; }

bool Potion::isPotion() const { return true; }

bool Potion::canCollect() { return true; }

Potion::~Potion() = default;

// provide a no‑op default for changeStatus()
// (since every subclass overrides it if needed)
void Potion::changeStatus() {}

void Potion::changeCollectStatus() {}
