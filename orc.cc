export module orc;
import enemy;

export class Orc : public Enemy {
 public:
    Orc();
    void attackEffect(Character &target) override;
};
