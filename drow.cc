export module drow;
import playercharacter;
import <string>;

export class Drow : public PlayerCharacter {
 public:
    Drow(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    void usePotion(std::string potionType) override;
};
