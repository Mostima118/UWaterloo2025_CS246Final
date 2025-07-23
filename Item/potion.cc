export module potion;

import item;

enum class PotionType {
    RH, // Restore HP
    BA, // Boost Atk
    BD, // Boost Def
    PH, // Poison HP
    WA, // Wound Atk
    WD  // Wound Def
};

export class Potion : public Item {
protected:
    PotionType potionType;
    // Default to be false, if used once, will be changed to true
    bool identified;

public:
    Potion(int r, int c, PotionType type);
    virtual ~Potion() = default;

    PotionType getPotionType() const;
    bool isIdentified() const;

    // Change identified to true
    void identify();

    bool isPotion() const override;

    // This return the symbol of the Gold
    char getSymbol() const;

    // Remember to change the name of the function to something like getNum
    char getSymbol() const override = 0;
    void use() override = 0;
};

export class RestoreHealthPotion : public Potion {
public:
    RestoreHealthPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};

export class BoostAtkPotion : public Potion {
public:
    BoostAtkPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};

export class BoostDefPotion : public Potion {
public:
    BoostDefPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};

export class PoisonHealthPotion : public Potion {
public:
    PoisonHealthPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};

export class WoundAtkPotion : public Potion {
public:
    WoundAtkPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};

export class WoundDefPotion : public Potion {
public:
    WoundDefPotion(int r, int c);
    char getSymbol() const override;
    void use(class Player& player) override;
};
