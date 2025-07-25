module halfling;

Halfling::Halfling(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

/*
void Halfling::defenseEffect(Character &attacker) {
    // generate random, e.g if = 0 then do effect otherwise do nothing
}
*/