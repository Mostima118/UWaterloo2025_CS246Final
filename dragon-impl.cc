module dragon;

Dragon::Dragon(int hp, int atk, int def, char mapSymbol, std::string type, Position hoardPos) : Enemy{hp, atk, def, mapSymbol, type}, hoardPos{hoardPos} {}

void Dragon::setHoardPos(int newX, int newY) {
    hoardPos.x = newX;
    hoardPos.y = newY;
}

Position Dragon::getHoardPos() const {
    return hoardPos;
}
