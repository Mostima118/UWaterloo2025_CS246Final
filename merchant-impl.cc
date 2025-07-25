module merchant;

bool Merchant::hostile = false;

Merchant::Merchant(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

int Merchant::dropGold() const {
    return 0; // no gold automatically added to player tally
}

bool Merchant::isHostile() { 
    return hostile; 
}

void Merchant::setHostile(bool newHostile) { 
    hostile = newHostile; 
}
