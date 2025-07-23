module dragon;

Dragon::Dragon(Position hoardPos) : Enemy{150, 20, 20, 'D', "Dragon"}, hoardPos{hoardPos} {}

Position Dragon::getHoardPos() const {
    return hoardPos;
}
