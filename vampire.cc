export module vampire;
import playercharacter;

export class Vampire : public PlayerCharacter {
 public:
    Vampire();
    void attackEffect(Character &target) override;
};
