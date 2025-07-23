export module goblin;
import playercharacter;

export class Goblin : public PlayerCharacter {
 public:
    Goblin();
    void attackEffect(Character &target) override;
};
