export module treasure;

import item;

export class Treasure : public Item {
protected:
    int value;

public:
    Treasure(int x, int y, int val);
    virtual ~Treasure() = default;

    int getValue() const;

    // This returns the symbol of Gold: 'G'
    char getSymbol() const;

    // Returns a number character representing type:
    // '6' = NormalGold, '7' = SmallGold, '8' = MerchantHoard, '9' = DragonHoard
    char getType() const override = 0;

    // Return false, treasure is not a potion
    bool isPotion() const override;

    // For DragonHoard: only collectible when dragon is slain
    virtual bool canCollect() const override = 0;

    // Adds value to player; only implemented in leaf classes
    //  Returns the value of the gold
    int use() const override = 0;
};

// Below are different types of treasure
export class NormalGold : public Treasure {
public:
    NormalGold(int x, int y);
    char getSymbol() const override;
    char getType() const override;
    int use() const override;
};

export class SmallGold : public Treasure {
public:
    SmallGold(int x, int y);
    char getSymbol() const override;
    char getType() const override;
    int use() const override;
};

export class MerchantHoard : public Treasure {
public:
    MerchantHoard(int x, int y);
    char getSymbol() const override;
    char getType() const override;
    int use(class Player& player) const override;
};

export class DragonHoard : public Treasure {
    bool dragonAlive;
public:
    DragonHoard(int x, int y, bool alive = true);
    char getSymbol() const override;
    char getType() const override;
    bool isCollectible() const override;
    int use(class Player& player) const override;
};
