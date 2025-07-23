export module drow;
import playercharacter;
import <string>;

export class Drow : public PlayerCharacter {
 public:
    Drow();
    void usePotion(std::string potionType) override;
};
