export module item;

import <memory>;
import <vector>;

export class Item {
protected:
    int x;
    int y;

public:
    Item(int x, int y);
    virtual ~Item() = default;

    int getX() const;
    int getY() const;

    // Reset the position
    void setPosition(int x, int y);

    // getType will return the preset number ('0' - '9') of each item
    virtual char getType() = 0;

    // use will return a string to represent the potion 
    //  or an int of it's applied on treasure
    // NEED TO BE FIXED //
    // Either overload use or make it return the same type
    virtual char use() = 0;

    // Symbol representation of potion "P" or treasure "G"
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const;

    // Create item based on the preset ('0' - '9'), used for testing purposes
    static std::unique_ptr<Item> createPreset(char itemType);

    // Random generation, potion
    static std::unique_ptr<Item> createRandomPotion(unsigned seed = 0);

    // Random generation, treasure
    static std::unique_ptr<Item> createRandomTreasure(unsigned seed = 0);
        
    // createGold creates two piles of normal gold when human is killed
    //  and one pile of merchant hoard when merchant is killed
    static std::unique_ptr<Item> createGold(char c);
};
