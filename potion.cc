export module potion;

import <string>;

import item;

enum class PotionType {
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
    virtual ~Potion() = default;

    // This function return the potion type
    //  Ex. RH, BA, BD ...
    PotionType getPotionType() const;

    // Return true if the potion is seen, false otherwise
    bool isSeen();

    // Change isSeen to true
    void See() override;

    bool isPotion() const override;

    bool canCollect() override;

    // This return the symbol of the potion -- "P"
    char getSymbol() const;

    int getValue() override;

    void changeStatus() override;

    // getType function returns the NUMBER correlated with the potion
    //  Ex. Restore Health (RH) is '0', Boost Atk (BA) is '1' ...
    char getType() override = 0;
    std::string use() override = 0;
};

// Below are the interfaces of different type of potions
// RH
export class RestoreHealthPotion : public Potion {
public:
    RestoreHealthPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};

// BA
export class BoostAtkPotion : public Potion {
public:
    BoostAtkPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};

// BD
export class BoostDefPotion : public Potion {
public:
    BoostDefPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};

// PH
export class PoisonHealthPotion : public Potion {
public:
    PoisonHealthPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};

// WA
export class WoundAtkPotion : public Potion {
public:
    WoundAtkPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};

// WD
export class WoundDefPotion : public Potion {
public:
    WoundDefPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
};
