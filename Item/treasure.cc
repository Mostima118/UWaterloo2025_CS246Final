export module treasure;

import item;

export class Treasure : public Item {
protected:
    int value;

public:
    Treasure(int r, int c, int val);
    virtual ~Treasure() = default;

    int getValue() const;

    // This return the symbol of the Gold
    char getSymbol() const;

    // Remember to change the name of the function to something like getNum
    char getSymbol() const override = 0;

    // This is for DragonHoard; the gold is presented 
    //  but cannot be picked up if dragon is not slain
    virtual bool isCollectible() const;

    void use(class Player& player) override;
};

export class NormalGold : public Treasure {
public:
    NormalGold(int r, int c);
    char getSymbol() const override;
};

export class SmallGold : public Treasure {
public:
    SmallGold(int r, int c);
    char getSymbol() const override;
};

export class MerchantHoard : public Treasure {
public:
    MerchantHoard(int r, int c);
    char getSymbol() const override;
};

export class DragonHoard : public Treasure {
    bool dragonAlive;
public:
    DragonHoard(int r, int c, bool alive = true);
    char getSymbol() const override;
    bool isCollectible() const override;
};
