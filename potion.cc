export module potion;

import <string>;

import item;

export enum class PotionType {
    RH, // Restore HP - 0
    BA, // Boost Atk - 1
    BD, // Boost Def - 2
    PH, // Poison HP - 3 
    WA, // Wound Atk - 4
    WD  // Wound Def - 5
};

export class Potion : public Item {
protected:
    // potionType will be one of the above 6 types
    PotionType potionType;
    // Default to be false, if used once, will be changed to true
    static bool seen[6];

public:
    Potion(int x, int y, PotionType type);
    virtual ~Potion();

    // This function return the potion type
    //  Ex. RH, BA, BD ...
    PotionType getPotionType() const;

    // Return true if the potion is seen, false otherwise
    bool isSeen() override;

    // Change isSeen to true
    void See() override;

    bool isPotion() const override;

    bool canCollect() override;

    // This return the symbol of the potion -- "P"
    char getSymbol() const;

    int getValue() override;

    void changeStatus() override;

    void changeCollectStatus() override;

    // getType function returns the NUMBER correlated with the potion
    //  Ex. Restore Health (RH) is '0', Boost Atk (BA) is '1' ...
    char getType() override = 0;
    std::string use() override = 0;
    virtual bool isDragonHoard() = 0;
};
