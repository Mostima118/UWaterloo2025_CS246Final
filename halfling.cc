export module halfling;
import enemy;

export class Halfling : public Enemy {
 public:
    Halfling();
    // void defenseEffect(Character &attacker) override; // no need bc handled in player attackeffect
};
