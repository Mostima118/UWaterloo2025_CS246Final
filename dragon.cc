export module dragon;
import Enemy;

export class Dragon : public Enemy {
    Position hoardPos;
 public:
    Dragon(Position hoardPos);
    void setHoardPos(int newX, int newY);
    Position getHoardPos() const;
};
