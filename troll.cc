export module troll;
import <string>;
import playercharacter;

export class Troll : public PlayerCharacter {
 public:
    Troll(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    void specialAbility() override;
};
