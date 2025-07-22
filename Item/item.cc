export module item;

export enum class ItemType {
    Potion,
    Treasure
};

export class Item {
protected:
    int row, col;
    ItemType type;

public:
    Item(int row, int col, ItemType type);
    virtual ~Item() = default;

    int getRow() const;
    int getCol() const;
    ItemType getType() const;

    virtual char getSymbol() const = 0;
};
