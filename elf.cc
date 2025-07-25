export module elf;
import <memory>;
import enemy;

export class Elf : public Enemy {
 public:
    Elf(int hp, int atk, int def, char mapSymbol, std::string type);
    int attackEffect(Character* target) override;
};
