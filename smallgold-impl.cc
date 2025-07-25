module smallgold;

import <string>;

// ===== SmallGold =====
SmallGold::SmallGold(int x, int y) : Treasure(x, y, 1) {}

char SmallGold::getSymbol() const {return 'G';}

char SmallGold::getType() { return '7'; }

bool SmallGold::canCollect() {
    return true;
}

std::string SmallGold::use() {
    return "7";
}

void SmallGold::changeStatus() { return; }

bool SmallGold::isDragonHoard() {
    return false;
}

void SmallGold::changeCollectStatus() {}
