export module orc;
import enemy;

export class Orc : public Enemy {
 public:
    Orc();
    void attackEffect(std::unique_ptr<Character> target) override;
};
