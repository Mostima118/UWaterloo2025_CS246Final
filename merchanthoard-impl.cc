module merchanthoard;

import <string>;

// ===== MerchantHoard =====
MerchantHoard::MerchantHoard(int x, int y) : Treasure(x, y, 4) {}

char MerchantHoard::getSymbol() const {return 'G';}

char MerchantHoard::getType() { return '8'; }

bool MerchantHoard::canCollect() {
    return true;
}

std::string MerchantHoard::use() {
    return "8";
}

void MerchantHoard::changeStatus() { return; }

bool MerchantHoard::isDragonHoard() {
    return false;
}

void MerchantHoard::changeCollectStatus() {}
