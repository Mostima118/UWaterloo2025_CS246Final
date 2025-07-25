export module playercharacter;
import character;
import <string>;
import <memory>;

export class PlayerCharacter : public Character {
 protected:
    int gold;
    int defaultAtk, defaultDef; // keep default values to reset at each floor
    std::string race;

 public:
    PlayerCharacter(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    virtual ~PlayerCharacter() = default;
    int getGold() const;
    void addGold(int amount);
    std::string getRace() const;

    void setAtk(int atkChange);
    void setDef(int atkChange);

    virtual void usePotion(std::string potionType);
    virtual void resetPotions();

    virtual int calculateScore() const;
    virtual int attackEffect(Character* target);
    //virtual void specialAbility() override;

};
