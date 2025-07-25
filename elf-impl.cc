module elf;
import <ctime>;
import <cstdlib>;
using namespace std;

Elf::Elf(int hp, int atk, int def, char mapSymbol, std::string type) : Enemy{hp, atk, def, mapSymbol, type} {}

int Elf::attackEffect(Character* target) {
    if (target == nullptr) {
        return 1;
    }

    //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
    //srand(time(0));
    int numhits = 0;

    int miss = rand() % 2;
    if (miss == 0) { // only hits 50% of the time
        int damage = target->calculateDamage(atk);
        target->setHP(target->getHP() - damage);
        ++numhits;
    }

    if (target->getType() != "Drow") {
        //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
        //srand(time(0));
        int miss = rand() % 2;
        if (miss == 0) { // only hits 50% of the time
            int damage = target->calculateDamage(atk);
            target->setHP(target->getHP() - damage);
            ++numhits;
        }
    }

    if (numhits == 0) {
        return 1;
    }
    else if (numhits == 1) {
        return 0;
    }
    else {
        return 2;
    }
}
