module human;
// need import gold

Human::Human(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

int Human::dropGold() const {
    return 0; // no gold automatically added, spawning of gold piles handled in engine
}
