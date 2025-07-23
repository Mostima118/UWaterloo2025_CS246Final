module orc;

using namespace std;

Orc::Orc() : Enemy{180, 30, 25, 'O', "Orc"} {}

void Orc::attackEffect(unique_ptr<Character> target) {
    if (target == nullptr) {
        return;
    }

    int damage = target->calculateDamage(atk);
    if (target->getType() == "Goblin") {
        damage = static_cast<int>(damage * 1.5);
    }
    target->setHP(target->getHP() - damage);
}
