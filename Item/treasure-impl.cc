module treasure;

Treasure::Treasure(int r, int c, int val) : Item(r, c), value{val} {}

int Treasure::getValue() const { return value; }

bool Treasure::isCollectible() const { return true; }

char Treasure::getSymbol() const { return 'G'; }

void Treasure::use(Player& player) {
    // Treasure picked up logic
    // Example, incrementing in-game gold count:
    //  player->addGold(value);
}

// NormalGold
NormalGold::NormalGold(int r, int c) : Treasure(r, c, 2) {}
char NormalGold::getSymbol() const { return '6'; }

// SmallGold
SmallGold::SmallGold(int r, int c) : Treasure(r, c, 1) {}
char SmallGold::getSymbol() const { return '7'; }

// MerchantHoard
MerchantHoard::MerchantHoard(int r, int c) : Treasure(r, c, 4) {}
char MerchantHoard::getSymbol() const { return '8'; }

// DragonHoard
DragonHoard::DragonHoard(int r, int c, bool alive) : Treasure(r, c, 6), dragonAlive{alive} {}
char DragonHoard::getSymbol() const { return '9'; }

// change this function to canCollect
bool DragonHoard::isCollectible() const {
    return !dragonAlive;
}

// bool canCollect