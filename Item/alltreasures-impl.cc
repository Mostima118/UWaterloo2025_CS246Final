module alltreasures;
import <iostream>; // if needed
import treasure;
import item;

NormalGold::NormalGold(int row, int col) : Treasure(row, col) {}

int NormalGold::getValue() const {
    return 2; // Normal gold value
}

char NormalGold::getSymbol() const {
    return '6'; //symbol for normal gold
}

SmallGold::SmallGold(int row, int col) : Treasure(row, col) {}

int SmallGold::getValue() const {
    return 1; // Small gold value
}

char SmallGold::getSymbol() const {
    return '7'; // symbol for Small gold
}

MerchantHoard::MerchantHoard(int row, int col) : Treasure(row, col) {}

int MerchantHoard::getValue() const {
    return 4; // Merchgold value
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
    return 6; // value for dragon hoard
}

char DragonHoard::getSymbol() const {
    return '9'; // symbol for dragon hoard
}
