module item;

import <cstdlib>;
import <memory>;
import allpotions;
import alltreasures;

Item::Item(int r, int c) : row{r}, col{c} {}

int Item::getRow() const { return row; }
int Item::getCol() const { return col; }

// This function is to change the coordinates of the item after created
//  Not necessarily needed
void Item::setPosition(int r, int c) { row = r; col = c; }

bool Item::isPotion() const { return false; }

std::unique_ptr<Item> Item::createRandomPotion() {
    int r = std::rand() % 6;
    switch (r) {
        case 0: return std::make_unique<RestoreHealthPotion>(-1, -1);
        case 1: return std::make_unique<BoostAtkPotion>(-1, -1);
        case 2: return std::make_unique<BoostDefPotion>(-1, -1);
        case 3: return std::make_unique<PoisonHealthPotion>(-1, -1);
        case 4: return std::make_unique<WoundAtkPotion>(-1, -1);
        case 5: return std::make_unique<WoundDefPotion>(-1, -1);
    }
    return nullptr;
}

std::unique_ptr<Item> Item::createRandomTreasure() {
    int r = std::rand() % 4;
    switch (r) {
        case 0: return std::make_unique<NormalGold>(-1, -1);
        case 1: return std::make_unique<SmallGold>(-1, -1);
        case 2: return std::make_unique<MerchantHoard>(-1, -1);
        case 3: return std::make_unique<DragonHoard>(-1, -1);
    }
    return nullptr;
}
