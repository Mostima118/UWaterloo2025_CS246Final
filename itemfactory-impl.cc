module itemfactory;

import <cstdlib>;
import <memory>;
import <vector>;
import <ctime>;
import potion;
import treasure;
import restorehealthpotion;
import boostatkpotion;
import boostdefpotion;
import poisonhealthpotion;
import woundatkpotion;
import wounddefpotion;
import normalgold;
import smallgold;
import merchanthoard;
import dragonhoard;

std::unique_ptr<Item> ItemFactory::createPreset(char itemType) {
    switch (itemType) {
        case '0': return std::make_unique<RestoreHealthPotion>(-1, -1);
        case '1': return std::make_unique<BoostAtkPotion>(-1, -1);
        case '2': return std::make_unique<BoostDefPotion>(-1, -1);
        case '3': return std::make_unique<PoisonHealthPotion>(-1, -1);
        case '4': return std::make_unique<WoundAtkPotion>(-1, -1);
        case '5': return std::make_unique<WoundDefPotion>(-1, -1);
        case '6': return std::make_unique<NormalGold>(-1, -1);
        case '7': return std::make_unique<SmallGold>(-1, -1);
        case '8': return std::make_unique<MerchantHoard>(-1, -1);
        case '9': return std::make_unique<DragonHoard>(-1, -1);
    }
    // Might need error handling based on the game engine
    return nullptr;
}

std::unique_ptr<Item> ItemFactory::createRandomPotion() {
    //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
    //std::srand(actual);
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

std::unique_ptr<Item> ItemFactory::createRandomTreasure() {
    //unsigned actual = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    //std::srand(actual);
    int r = std::rand() % 8;
    if (r < 5) {
        return std::make_unique<NormalGold>(-1, -1);
    } else if (r == 5) {
        return std::make_unique<DragonHoard>(-1, -1);
    } else {
        return std::make_unique<SmallGold>(-1, -1);
    }
}

std::unique_ptr<Item> ItemFactory::createGold(char c) {
    if (c == 'H') {
        return std::make_unique<MerchantHoard>(-1, -1);
    } else if (c == 'M') {
        return std::make_unique<MerchantHoard>(-1, -1);
    }
    return nullptr;
}
