export module potion;
import item;

export enum class PotionType {
    RH, // Restore Health
    BA, // Boost Atk
    BD, // Boost Def
    PH, // Poison Health
    WA, // Wound Atk
    WD  // Wound Def
};

export class Potion : public Item {
    PotionType potionType;
    bool identified;

public:
    Potion(int row, int col, PotionType type);

    PotionType getPotionType() const;
    bool isIdentified() const;
    void identify();

    char getSymbol() const override;

    ~Potion() = default;
};
