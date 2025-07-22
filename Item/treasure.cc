export module treasure;
import item;

export enum class TreasureType {
    Normal,
    Small,
    MerchantHoard,
    DragonHoard
};

export class Treasure : public Item {
protected:
    TreasureType treasureType;
    int value;

public:
    Treasure(int row, int col, TreasureType type);

    TreasureType getTreasureType() const;
    int getValue() const;
    char getSymbol() const override;

    virtual bool isCollectible() const;
    
    virtual ~Treasure() = default;
};
