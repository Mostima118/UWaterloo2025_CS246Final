export module enemy;
import character;
import <string>;


export class Enemy : public Character {
 public:
    Enemy(int hp, int atk, int def, char mapSymbol, std::string type);
    virtual ~Enemy() = default;
    virtual int dropGold() const;

    void attackEffect(Character &target);

};
