export module merchant;
import <string>;
import enemy;

export class Merchant : public Enemy {
 public:
    Merchant(int hp, int atk, int def, char mapSymbol, std::string type);
    int dropGold() const override;
};

