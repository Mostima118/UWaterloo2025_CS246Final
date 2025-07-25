export module shade;
import <string>;
import playercharacter;

export class Shade : public PlayerCharacter {
 public:
    Shade(int hp, int maxHP, int atk, int def, char mapSymbol, std::string type, std::string race);
    int calculateScore() const override;
};
