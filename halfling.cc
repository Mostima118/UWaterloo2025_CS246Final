export module halfling;
import <string>;
import enemy;

export class Halfling : public Enemy {
 public:
    Halfling(int hp, int atk, int def, char mapSymbol, std::string type);
    // void defenseEffect(Character &attacker) override; // no need bc handled in player attackeffect
};
