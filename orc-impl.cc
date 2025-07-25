module orc;

using namespace std;

Orc::Orc(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

void Orc::attackEffect(Character* target) {
    if (target == nullptr) {
        return;
    }

    int damage = target->calculateDamage(atk);
    if (target->getType() == "Goblin") {
        damage = static_cast<int>(damage * 1.5);
    }
    target->setHP(target->getHP() - damage);
}
