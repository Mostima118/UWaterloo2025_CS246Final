// item.cc — Interface
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
    void setPosition(int x, int y);

    // Remember to add this function to potion
    //  Potion will return it's type
    //   Do nothing for treasure
    virtual void getType() = 0;
    virtual void use() = 0;
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const;

    std::unique_ptr<Item> createPreset(char itemType);
    static std::unique_ptr<Item> createRandomPotion(unsigned seed = 0);
    static std::unique_ptr<Item> createRandomTreasure(unsigned seed = 0);
        
    // Add makeUnique that create two piles of normal gold when human is killed
    static std::unique_ptr<Item> createGold(char c);
};
