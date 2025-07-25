export module orc;
import <memory>;
import enemy;

export class Orc : public Enemy {
 public:
    Orc(int hp, int atk, int def, char mapSymbol, std::string type);
    void attackEffect(Character* target) override;
};
