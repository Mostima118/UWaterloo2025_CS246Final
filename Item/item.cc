export module item;

import <memory>;

export class Item {
protected:
    int x;
    int y;

public:
    Item(int x, int y);
    virtual ~Item() = default;

    int getX() const;
    int getY() const;

    // Reset the postion
    void setPosition(int x, int y);

    // getType will return the preset number ('0' - '9') of each item
    virtual void getType() = 0;

    // use will return a char to represent the potion 
    //  or an int of it's applied on treasure
    virtual void use() = 0;

    // Symbol representation of potion "P" or treasure "G"
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const;

    // Create item based on the preset ('0' - '9'), used for testing purposes
    std::unique_ptr<Item> createPreset(char itemType);

    // Random generation, potion
    static std::unique_ptr<Item> createRandomPotion(unsigned seed = 0);

    // Random generation, treasure
    static std::unique_ptr<Item> createRandomTreasure(unsigned seed = 0);
        
    // Add makeUnique that create two piles of normal gold when human is killed
    static std::unique_ptr<Item> createGold(char c);
};
