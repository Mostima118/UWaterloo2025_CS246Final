export module goblin;
import <memory>;
import <string>;
import playercharacter;

export class Goblin : public PlayerCharacter {
 public:
    Goblin(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    int attackEffect(Character* target) override;
};
