export module goblin;
import playercharacter;

export class Goblin : public PlayerCharacter {
 public:
    Goblin();
    void attackEffect(std::unique_ptr<Character> target) override;
};
