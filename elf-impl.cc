module elf;

using namespace std;

Elf::Elf() : Enemy{140, 30, 10, 'E', "Elf"} {}

void Elf::attackEffect(unique_ptr<Character> target) {
    if (target == nullptr) {
        return;
    }

    Enemy::attackEffect(target);
    if (target->getType() != "Drow") {
        Enemy::attackEffect(target);
    }
}
