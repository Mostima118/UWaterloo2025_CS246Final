export module itemfactory;

import <memory>;
import <vector>;

import item;
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

export class ItemFactory {
public:
    // Create item based on the preset ('0' - '9'), used for testing purposes
    static std::unique_ptr<Item> createPreset(char itemType);

    // Random generation, potion
    static std::unique_ptr<Item> createRandomPotion();

    // Random generation, treasure
    static std::unique_ptr<Item> createRandomTreasure();
        
    // createGold creates two piles of normal gold when human is killed
    //  and one pile of merchant hoard when merchant is killed
    static std::unique_ptr<Item> createGold(char c);
};
