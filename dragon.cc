export module dragon;
import <string>;
import enemy;
import position;


export class Dragon : public Enemy {
    Position hoardPos;
 public:
    Dragon(int hp, int atk, int def, char mapSymbol, std::string type, Position hoardPos);
    void setHoardPos(int newX, int newY);
    Position getHoardPos() const;
};
