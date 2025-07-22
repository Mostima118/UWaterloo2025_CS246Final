module treasure;

Treasure::Treasure(int r, int c, int val) : Item(r, c), value{val} {}

int Treasure::getValue() const { return value; }

char Treasure::getSymbol() const { return 'G'; }

bool Treasure::isCollectible() const { return true; }

void Treasure::use() {
    // Treasure picked up logic
    // Example, incrementing in-game gold count:
    //  player->addGold(value);
}

// NormalGold
NormalGold::NormalGold(int r, int c) : Treasure(r, c, 2) {}
int NormalGold::getValue() const { return 2; }
char NormalGold::getSymbol() const { return '6'; }

// SmallGold
SmallGold::SmallGold(int r, int c) : Treasure(r, c, 1) {}
int SmallGold::getValue() const { return 1; }
char SmallGold::getSymbol() const { return '7'; }

// MerchantHoard
MerchantHoard::MerchantHoard(int r, int c) : Treasure(r, c, 4) {}
int MerchantHoard::getValue() const { return 4; }
char MerchantHoard::getSymbol() const { return '8'; }

// DragonHoard
DragonHoard::DragonHoard(int r, int c, bool alive) : Treasure(r, c, 6), dragonAlive{alive} {}
int DragonHoard::getValue() const { return 6; }
char DragonHoard::getSymbol() const { return '9'; }

bool DragonHoard::isCollectible() const {
    return !dragonAlive;
}
