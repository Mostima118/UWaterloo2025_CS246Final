export module character;
import <string>;
import <memory>;
import position;


export class Character {
 protected:
   int hp, maxHP, atk, def;
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
   
   // MAYBE NEED TO MAKE PURE VIRTUAL AGAIN LATER
   virtual void specialAbility();

   // take pointer so if target not found have null ptr and just do nothing
   virtual int attackEffect(Character* target);
   //virtual void defenseEffect(Character &attacker); // not actually necessary? can just have effects in attack

};
