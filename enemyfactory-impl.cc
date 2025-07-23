module enemyfactory;
import enemy;
import human;
import dwarf;
import halfling;
import elf;
import orc;
import merchant;
import dragon;
import <string>;
import <memory>;
import <cstdlib>;
import <ctime>;

using namespace std;

unique_ptr<Enemy> EnemyFactory::createRandomEnemy() {
    srand(time(0));
    int whichEnemy = rand() % 18; // get a number from 0 to 17
    if (whichEnemy < 4) { // if 0 to 3 (i.e. a 4/18 chance) spawn a human
        return createEnemy("h");
    }
    else if (whichEnemy < 7) { // similar for dwarf (and all others after)
        return createEnemy("w");
    }
    else if (whichEnemy < 12) {
        return createEnemy("l");
    }
    else if (whichEnemy < 14) {
        return createEnemy("e");
    }
    else if (whichEnemy < 16) {
        return createEnemy("o");
    }
    else {
        return createEnemy("m");
    }
}

unique_ptr<Enemy> EnemyFactory::createEnemy(const string &type) {
    if (type == "h") {
        return make_unique<Human>(140, 140, 20, 20, 'H', "Human");
    } else if (type == "w") {
        return make_unique<Dwarf>(100, 100, 20, 30, 'W', "Dwarf");
    } else if (type == "e") {
        return make_unique<Elf>(140, 140, 30, 10, 'E', "Elf");
    } else if (type == "o") {
        return make_unique<Orc>(180, 180, 30, 25, 'O', "Orc");
    } else if (type == "m") {
        return make_unique<Merchant>(30, 30, 70, 5, 'M', "Merchant");
    } else if (type == "d") {
        return make_unique<Dragon>(150, 150, 20, 20, 'D', "Dragon");
    } else if (type == "l") {
        return make_unique<Halfling>(100, 100, 15, 20, 'L', "Halfling");
    }
    return nullptr;
}
