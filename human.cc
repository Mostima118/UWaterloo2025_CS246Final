export module human;
import <string>;
import enemy;

export class Human : public Enemy {
 public:
    Human(int hp, int atk, int def, char mapSymbol, std::string type);
    int dropGold() const override;
};
