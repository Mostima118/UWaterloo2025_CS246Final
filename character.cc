export module character;
import <string>;


struct Position {
  int x, y;
  Position(int x, int y): x{x}, y{y} {};
};

export class Character {
 protected:
   int hp, maxHp, atk, def;
   char mapSymbol;
   std::string type;
   Position pos;


 public:
   Character(int hp, int maxHp, int atk, int def, char mapSymbol, std::string type);
   virtual ~Character() = default;
   
   int getHP() const;
   int getMaxHP() const;
   int getAtk() const;
   int getDef() const;
   char getSymbol() const;
   std::string getType() const;
   Position getPosition() const;
   bool isAlive() const;

   void setHP(int newHP);
   void setPosition(int newX, int newY);

   int calculateDamage(int attackerAtk) const;
   
   virtual void applySpecialAbility() = 0;
   virtual void attackEffect(Character &target);
   //virtual void defenseEffect(Character &attacker); // not actually necessary? can just have effects in attack

};
