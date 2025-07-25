export module enemy;
import character;
import position;
import <string>;
import <memory>;


export class Enemy : public Character {
 protected:
    static bool hostile;
    Position hoardPos;
 public:
    Enemy(int hp, int atk, int def, char mapSymbol, std::string type);
    virtual ~Enemy() = default;
    virtual int dropGold() const;

    int attackEffect(Character* target);
    
    static bool isHostile();
    static void setHostile(bool hostile);

    void setHoardPos(Position newPos);
    Position getHoardPos() const;

};
