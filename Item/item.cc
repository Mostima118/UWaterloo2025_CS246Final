// Change the row and column to x and y
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

    // Remember to add this function to potion
    //  Potion will return it's type
    //   Do nothing for treasure
    virtual void getType() = 0;
    
    // Delete this
    virtual void use() = 0;
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const;

    static std::unique_ptr<Item> createRandomPotion();
    static std::unique_ptr<Item> createRandomTreasure();

    // Add makeUnique that create two piles of normal gold when human is killed
    static std::unique_ptr<Item> makeUnique();
};
