module alltreasures;
import <iostream>; // if needed
import treasure;
import item;

NormalGold::NormalGold(int row, int col) : Treasure(row, col) {}

int NormalGold::getValue() const {
    return 2; // Example gold value
}

char NormalGold::getSymbol() const {
    return '6'; // or whatever symbol you want for normal gold
}

SmallGold::SmallGold(int row, int col) : Treasure(row, col) {}

int SmallGold::getValue() const {
    return 1; // Example small gold value
}

char SmallGold::getSymbol() const {
    return '7'; // symbol for small gold
}

MerchantHoard::MerchantHoard(int row, int col) : Treasure(row, col) {}

int MerchantHoard::getValue() const {
    return 4; // example value
}

char MerchantHoard::getSymbol() const {
    return '8'; // symbol for merchant hoard
}

DragonHoard::DragonHoard(int row, int col, bool dragonAlive)
    : Treasure(row, col), dragonAlive{dragonAlive} {}

bool DragonHoard::isCollectible() const {
    return !dragonAlive;
}

int DragonHoard::getValue() const {
    return 6; // example value for dragon hoard
}

char DragonHoard::getSymbol() const {
    return '9'; // symbol for dragon hoard
}
