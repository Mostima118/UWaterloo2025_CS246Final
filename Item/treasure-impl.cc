module treasure;

Treasure::Treasure(int x, int y, int val) : Item(x, y), value{val} {}

int Treasure::getValue() const { return value; }

bool Treasure::canCollect() const { return true; }

bool Treasure::isPotion() const { return false; }

char Treasure::getSymbol() const { return 'G'; }

// ===== NormalGold =====
NormalGold::NormalGold(int x, int y) : Treasure(x, y, 2) {}

char NormalGold::getType() const { return '6'; }

bool NormalGold::canCollect() const {
    return true;
}

int NormalGold::use() const {
    return value;
}

// ===== SmallGold =====
SmallGold::SmallGold(int x, int y) : Treasure(x, y, 1) {}

char SmallGold::getType() const { return '7'; }

bool SmallGold::canCollect() const {
    return true;
}

int SmallGold::use() const {
    return value;
}

// ===== MerchantHoard =====
MerchantHoard::MerchantHoard(int x, int y) : Treasure(x, y, 4) {}

char MerchantHoard::getType() const { return '8'; }

bool MerchantHoard::canCollect() const {
    return true;
}

int MerchantHoard::use() const {
    return value;
}

// ===== DragonHoard =====
DragonHoard::DragonHoard(int x, int y, bool alive) 
    : Treasure(x, y, 6), status{false}, collectStatus{false} {}

char DragonHoard::getType() const { return '9'; }

int DragonHoard::use() const {
    return value;
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

bool DragonHoard::canCollect() const {
    return collectStatus;
}

void DragonHoard::changeCollectStatus() {
    collectStatus = !collectStatus;
}
