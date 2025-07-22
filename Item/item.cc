/////////////////////////////////NEED RANDOM GENERATION///////////////////////////////////
// How to ensure some potions have permanent effect but others dont
export module item;

import <memory>;

export class Item {
protected:
    int row;
    int col;

public:
    Item(int r, int c);
    virtual ~Item() = default;

    int getRow() const;
    int getCol() const;
    void setPosition(int r, int c);

    virtual void use() = 0;
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const;

    static std::unique_ptr<Item> createRandomPotion();
    static std::unique_ptr<Item> createRandomTreasure();
};
