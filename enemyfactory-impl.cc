module enemyfactory;
import enemy;
import human;
import dwarf;
import halfling;
import elf;
import orc;
import merchant;
import dragon;
import position;
import <iostream>;
import <string>;
import <memory>;
import <cstdlib>;
import <ctime>;

using namespace std;

unique_ptr<Enemy> EnemyFactory::createRandomEnemy() {
    //unsigned actual = seed == 0 ? static_cast<unsigned>(time(nullptr)) : seed;
    
    int whichEnemy = rand() % 18; // get a number from 0 to 17
    
    if (whichEnemy < 4) { // if 0 to 3 (i.e. a 4/18 chance) spawn a human
        return createEnemy('H');
    }
    else if (whichEnemy < 7) { // similar for dwarf (and all others after)
        return createEnemy('W');
    }
    else if (whichEnemy < 12) {
        
        return createEnemy('L');
    }
    else if (whichEnemy < 14) {
        return createEnemy('E');
    }
    else if (whichEnemy < 16) {
        return createEnemy('O');
    }
    else {
        return createEnemy('M');
    }
}

unique_ptr<Enemy> EnemyFactory::createEnemy(const char &type) {
    if (type == 'H') {
        return make_unique<Human>(140, 20, 20, 'H', "Human");
    } else if (type == 'W') {
        return make_unique<Dwarf>(100, 20, 30, 'W', "Dwarf");
    } else if (type == 'E') {
        return make_unique<Elf>(140, 30, 10, 'E', "Elf");
    } else if (type == 'O') {
        return make_unique<Orc>(180, 30, 25, 'O', "Orc");
    } else if (type == 'M') {
        return make_unique<Merchant>(30, 70, 5, 'M', "Merchant");
    } else if (type == 'D') {
        return make_unique<Dragon>(150, 20, 20, 'D', "Dragon", Position{0, 0});
    } else if (type == 'L') {
        return make_unique<Halfling>(100, 15, 20, 'L', "Halfling");
    }
    return nullptr;
}
