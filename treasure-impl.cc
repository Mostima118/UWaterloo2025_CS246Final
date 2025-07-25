module treasure;

import <string>;

Treasure::Treasure(int x, int y, int val) : Item(x, y), value{val} {}

int Treasure::getValue() { return value; }

bool Treasure::canCollect() { return true; }

bool Treasure::isPotion() const { return false; }

char Treasure::getSymbol() const { return 'G'; }

void Treasure::See() { return; }

// ===== NormalGold =====
NormalGold::NormalGold(int x, int y) : Treasure(x, y, 2) {}

char NormalGold::getType() { return '6'; }

bool NormalGold::canCollect() {
    return true;
}

std::string NormalGold::use() {
    return "6";
}

void NormalGold::changeStatus() { return; }

// ===== SmallGold =====
SmallGold::SmallGold(int x, int y) : Treasure(x, y, 1) {}

char SmallGold::getType() { return '7'; }

bool SmallGold::canCollect() {
    return true;
}

std::string SmallGold::use() {
    return "7";
}

void SmallGold::changeStatus() { return; }

// ===== MerchantHoard =====
MerchantHoard::MerchantHoard(int x, int y) : Treasure(x, y, 4) {}

char MerchantHoard::getType() { return '8'; }

bool MerchantHoard::canCollect() {
    return true;
}

std::string MerchantHoard::use() {
    return "8";
}

void MerchantHoard::changeStatus() { return; }

// ===== DragonHoard =====
DragonHoard::DragonHoard(int x, int y, bool alive) 
    : Treasure(x, y, 6), status{false}, collectStatus{false} {}

char DragonHoard::getType() { return '9'; }

std::string DragonHoard::use() {
    return "9";
}

bool DragonHoard::isDragonHoard() const {
    return true;
}

bool DragonHoard::getStatus() const {
    return status;
}

void DragonHoard::changeStatus() {
    status = !status;
}

bool DragonHoard::canCollect() {
    return collectStatus;
}

void DragonHoard::changeCollectStatus() {
    collectStatus = !collectStatus;
}
