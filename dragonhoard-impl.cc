module dragonhoard;

import <string>;

// ===== DragonHoard =====
DragonHoard::DragonHoard(int x, int y, bool alive) 
    : Treasure(x, y, 6), status{false}, collectStatus{false} {}

char DragonHoard::getSymbol() const {return 'G';}

char DragonHoard::getType() { return '9'; }

std::string DragonHoard::use() {
    return "9";
}

bool DragonHoard::isDragonHoard() {
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
