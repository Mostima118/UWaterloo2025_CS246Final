export module potion;

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
    bool identified;

public:
    Potion(int x, int y, PotionType type);
    virtual ~Potion() = default;

    // This function return the potion type
    //  Ex. RH, BA, BD ...
    PotionType getPotionType() const;
    bool isIdentified() const;

    // Change identified to true
    void identify();

    bool isPotion() const override;

    // This return the symbol of the potion -- "P"
    char getSymbol() const;

    // getType function returns the NUMBER correlated with the potion
    //  Ex. Restore Health (RH) is '0', Boost Atk (BA) is '1' ...
    char getType() const override = 0;
    void use() override = 0;
};

// Below are the interfaces of different type of potions
// RH
export class RestoreHealthPotion : public Potion {
public:
    RestoreHealthPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};

// BA
export class BoostAtkPotion : public Potion {
public:
    BoostAtkPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};

// BD
export class BoostDefPotion : public Potion {
public:
    BoostDefPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};

// PH
export class PoisonHealthPotion : public Potion {
public:
    PoisonHealthPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};

// WA
export class WoundAtkPotion : public Potion {
public:
    WoundAtkPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};

// WD
export class WoundDefPotion : public Potion {
public:
    WoundDefPotion(int x, int y);
    char getSymbol() const override;
    void use(class Player& player) override;
};
