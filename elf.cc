export module elf;
import enemy;

export class Elf : public Enemy {
 public:
    Elf();
    void attackEffect(std::unique_ptr<Character> target) override;
};