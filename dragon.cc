export module dragon;
import Enemy;

export class Dragon : public Enemy {
    Position hoardPos;
 public:
    Dragon(Position hoardPos);
    Position getHoardPos() const;
};
