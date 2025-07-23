module itemfactory;

import <cstdlib>;
import <memory>;
import item;

std::unique_ptr<Item> createPreset(char itemType) {
    return Item::createPreset(itemType);
}

std::unique_ptr<Item> ItemFactory::createRandomPotion(unsigned seed) {
    return Item::createRandomPotion(seed);
}

std::unique_ptr<Item> ItemFactory::createRandomTreasure(unsigned seed) {
    return Item::createRandomTreasure(seed);
}

std::vector<std::unique_ptr<Item>> Item::createGold(char c) {
    return Item::createGold(c);
}