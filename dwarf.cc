export module dwarf;
import <string>;
import enemy;

export class Dwarf : public Enemy {
 public:
    Dwarf(int hp, int atk, int def, char mapSymbol, std::string type);
    //void defenseEffect(Character &attacker) override; no need bc already in vampire?
};
