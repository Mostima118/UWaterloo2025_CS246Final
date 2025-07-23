export module shade;
import playercharacter;

export class Shade : public PlayerCharacter {
 public:
    Shade();
    int calculateScore() const override;
};
