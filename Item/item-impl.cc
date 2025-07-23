module item;

import <cstdlib>;
import <memory>;
import potion;
import treasure;

Item::Item(int x, int y) : x{x}, y{y} {}

int Item::getRow() const { return x; }
int Item::getCol() const { return y; }

// This function is to change the coordinates of the item after created
void Item::setPosition(int x, int y) { this->x = x; this->y = y; }

bool Item::isPotion() const { return false; }

std::unique_ptr<Item> Item::createRandomPotion(unsigned seed) {
    unsigned actual = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    std::srand(actual);
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

std::unique_ptr<Item> Item::createRandomTreasure(unsigned seed) {
    unsigned actual = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    std::srand(actual);
    int r = std::rand() % 8;
    if (r < 5) {
        return std::make_unique<NormalGold>(-1, -1);
    } else if (r == 5) {
        return std::make_unique<DragonHoard>(-1, -1);
    } else {
        return std::make_unique<SmallGold>(-1, -1);
    }
}

std::vector<std::unique_ptr<Item>> Item::createGold(char c) {
    std::vector<std::unique_ptr<Item>> goldItems;
    if (c == 'H') {
        goldItems.emplace_back(std::make_unique<NormalGold>(-1, -1));
        goldItems.emplace_back(std::make_unique<NormalGold>(-1, -1));
    } else if (c == 'M') {
        goldItems.emplace_back(std::make_unique<MerchantHoard>(-1, -1));
    }
    return goldItems;
}
