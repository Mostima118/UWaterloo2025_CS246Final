module potion;
import item;

Potion::Potion(int row, int col, PotionType type)
    : Item{row, col, ItemType::Potion}, potionType{type}, identified{false} {}

PotionType Potion::getPotionType() const { return potionType; }
bool Potion::isIdentified() const { return identified; }
void Potion::identify() { identified = true; }

char Potion::getSymbol() const { return 'P'; }
