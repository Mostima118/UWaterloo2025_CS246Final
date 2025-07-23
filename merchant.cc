export module merchant;
import Enemy;

export class Merchant : public Enemy {
    static bool hostile;
 public:
    Merchant();
    static bool isHostile() const;
    static void setHostile(bool hostile);
    int dropGold() const override;
};
