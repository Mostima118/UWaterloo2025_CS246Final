export module vampire;
import playercharacter;

export class Vampire : public PlayerCharacter {
 public:
    Vampire();
    void attackEffect(std::unique_ptr<Character> target) override;
};
