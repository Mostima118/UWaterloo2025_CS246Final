module dwarf;

Dwarf::Dwarf(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

// don't need to have on defend bc effect already in vampire's?
