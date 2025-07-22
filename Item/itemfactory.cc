export module itemfactory;

import <memory>;
import item;

export class ItemFactory {
public:
    static std::unique_ptr<Item> createRandomPotion();
    static std::unique_ptr<Item> createRandomTreasure();
};
