module orc;

using namespace std;

Orc::Orc(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

int Orc::attackEffect(Character* target) {
    if (target == nullptr) {
        return 1;
    }
    //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
    //srand(time(0));
    int miss = rand() % 2;
    if (miss == 0) { // only hits 50% of the time
        int damage = target->calculateDamage(atk);
        if (target->getType() == "Goblin") {
            damage = static_cast<int>(damage * 1.5);
        }
        target->setHP(target->getHP() - damage);
        return 0;
    }

    return 1;
}
