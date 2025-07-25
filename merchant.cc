export module merchant;
import <string>;
import enemy;

export class Merchant : public Enemy {
    static bool hostile;
 public:
    Merchant(int hp, int atk, int def, char mapSymbol, std::string type);
    static bool isHostile();
    static void setHostile(bool hostile);
    int dropGold() const override;
};
