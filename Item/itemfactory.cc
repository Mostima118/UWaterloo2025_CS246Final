export module itemfactory;

import <memory>;
import item;

export class ItemFactory {
public:
    static std::unique_ptr<Item> createPreset(char itemType);
    static std::unique_ptr<Item> createRandomPotion(unsigned seed);
    static std::unique_ptr<Item> createRandomTreasure(unsigned seed);
    static std::vector<std::unique_ptr<Item>> createGold(char c);
};
