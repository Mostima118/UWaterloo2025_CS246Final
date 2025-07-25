export module dragon;
import <string>;
import enemy;
import position;


export class Dragon : public Enemy {
 public:
    Dragon(int hp, int atk, int def, char mapSymbol, std::string type, Position newHoardPos);
};
