module dragon;

Dragon::Dragon(int hp, int atk, int def, char mapSymbol, std::string type, Position newHoardPos) : Enemy{hp, atk, def, mapSymbol, type} {
    Enemy::setHoardPos(newHoardPos);
}
