module itemfactory;

import <cstdlib>;
import <memory>;
import item;

std::unique_ptr<Item> createPreset(char itemType) {
    return Item::createPreset(itemType);
}

std::unique_ptr<Item> ItemFactory::createRandomPotion() {
    return Item::createRandomPotion();
}

std::unique_ptr<Item> ItemFactory::createRandomTreasure() {
    return Item::createRandomTreasure();
}
