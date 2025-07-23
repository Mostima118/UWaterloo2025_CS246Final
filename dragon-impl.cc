module dragon;

Dragon::Dragon(Position hoardPos) : Enemy{150, 20, 20, 'D', "Dragon"}, hoardPos{hoardPos} {}

void Dragon::setHoardPos(int newX int newY) {
    hoardPos.x = newX;
    hoardPos.y = newY;
}

Position Dragon::getHoardPos() const {
    return hoardPos;
}
