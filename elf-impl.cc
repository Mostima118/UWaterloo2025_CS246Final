module elf;

Elf::Elf() : Enemy{140, 30, 10, 'E', "Elf"} {}

void Elf::attackEffect(Character &target) {
    Enemy::attackEffect(target);
    if (target.getType() != "Drow") {
        Enemy::attackEffect(target);
    }
}
