export module troll;
import playercharacter;

export class Troll : public PlayerCharacter {
 public:
    Troll();
    void specialAbility() override;
};
