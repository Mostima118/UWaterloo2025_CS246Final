export module vampire;
import <memory>;
import <string>;
import playercharacter;

export class Vampire : public PlayerCharacter {
 public:
    Vampire(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    int attackEffect(Character* target) override;
};
