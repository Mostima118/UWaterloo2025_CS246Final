export module human;
import enemy;

export class Human : public Enemy {
 public:
    Human();
    int dropGold() const override;
};
