export module potions;
import potion;

// Restore Health
export class RestoreHealthPotion : public Potion {
public:
    RestoreHealthPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};

// Boost Atk
export class BoostAtkPotion : public Potion {
public:
    BoostAtkPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};

// Boost Def
export class BoostDefPotion : public Potion {
public:
    BoostDefPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};

// Poison Health
export class PoisonHealthPotion : public Potion {
public:
    PoisonHealthPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};

// Wound Atk
export class WoundAtkPotion : public Potion {
public:
    WoundAtkPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};

// Wound Def
export class WoundDefPotion : public Potion {
public:
    WoundDefPotion(int row, int col);
    void applyTo(Player& player);
    char getSymbol() const override;
};
