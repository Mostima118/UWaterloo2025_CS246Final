module treasure;

Treasure::Treasure(int row, int col, TreasureType type)
    : Item{row, col}, treasureType{type} {
    switch (type) {
        case TreasureType::Small:
            value = 1;
            break;
        case TreasureType::Normal:
            value = 2;
            break;
        case TreasureType::MerchantHoard:
            value = 4;
            break;
        case TreasureType::DragonHoard:
            value = 6;
            break;
    }
}

TreasureType Treasure::getTreasureType() const {
    return treasureType;
}

int Treasure::getValue() const {
    return value;
}

bool Treasure::isCollectible() const {
    return true; // default behavior for all non-DragonHoard
}

char Treasure::getSymbol() const {
    return 'G';
}
