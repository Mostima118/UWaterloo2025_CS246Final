module merchant;

bool Merchant::hostile = false;

Merchant::Merchant() : Enemy{30, 70, 5, 'M', "Merchant"} {}

int Merchant::dropGold() const {
    return 0; // no gold automatically added to player tally
}

bool Merchant::isHostile() const { 
    return hostile; 
}

void Merchant::setHostile(bool newHostile) { 
    hostile = newHostile; 
}
