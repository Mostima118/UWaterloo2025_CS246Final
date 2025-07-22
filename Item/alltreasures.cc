export module alltreasures;
import item;
import treasure;

export class NormalGold : public Treasure {
public:
    NormalGold(int row, int col);
    int getValue() const override;
    char getSymbol() const override;
};

export class SmallGold : public Treasure {
public:
    SmallGold(int row, int col);
    int getValue() const override;
    char getSymbol() const override;
};

export class MerchantHoard : public Treasure {
public:
    MerchantHoard(int row, int col);
    int getValue() const override;
    char getSymbol() const override;
};

class DragonHoard : public Treasure {
    bool dragonAlive;  // NEW

public:
    DragonHoard(int row, int col, bool dragonAlive = true);

    int getValue() const override;
    char getSymbol() const override;
    bool isCollectible() const override; // override
};
