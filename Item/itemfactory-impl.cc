module itemfactory;

import <cstdlib>;
import <memory>;
import item;

std::unique_ptr<Item> ItemFactory::createRandomPotion() {
    return Item::createRandomPotion();
}

std::unique_ptr<Item> ItemFactory::createRandomTreasure() {
    return Item::createRandomTreasure();
}
