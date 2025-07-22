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

    // If identified, potion effect is known
    bool identified;

public:
    // The potion will first be constructed as unknown to the player
    Potion(int row, int col, PotionType type);

    PotionType getPotionType() const;
    bool isIdentified() const;
    
    // Modify the identified field to true
    void identify();

    char getSymbol() const override;

    ~Potion() = default;
};
