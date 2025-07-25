module treasure;

import <string>;

Treasure::Treasure(int x, int y, int val) : Item(x, y), value{val} {}

int Treasure::getValue() { return value; }

bool Treasure::canCollect() { return true; }

Treasure::~Treasure() = default;

bool Treasure::isPotion() const { return false; }

char Treasure::getSymbol() const { return 'G'; }

void Treasure::See() { return; }

bool Treasure::isSeen() { return true; }
