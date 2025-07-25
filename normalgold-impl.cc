module normalgold;

import <string>;

// ===== NormalGold =====
NormalGold::NormalGold(int x, int y) : Treasure(x, y, 2) {}

char NormalGold::getSymbol() const {return 'G';}

char NormalGold::getType() { return '6'; }

bool NormalGold::canCollect() {
    return true;
}

std::string NormalGold::use() {
    return "6";
}

void NormalGold::changeStatus() { return; }

bool NormalGold::isDragonHoard() {
    return false;
}

void NormalGold::changeCollectStatus() {}
