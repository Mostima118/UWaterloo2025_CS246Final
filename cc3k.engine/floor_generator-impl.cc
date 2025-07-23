module floor;
import <fstream>;
import <string>;
import <vector>;
import <cstdlib>;
import <ctime>;
import item;
import enemy;

namespace cc3k {

void FloorGenerator::loadLayout(const std::string& filename) {
    std::ifstream fin(filename);
    map_.clear(); std::string line;
    while (std::getline(fin, line)) map_.push_back(line);
}

void FloorGenerator::generateRandomFloor(unsigned) {
    loadLayout("default_floor.txt");
}

const std::vector<std::string>& FloorGenerator::getMap() const {
    return map_;
}

std::vector<std::unique_ptr<Item>> FloorGenerator::spawnItems(unsigned seed) const {
    unsigned actual = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    std::srand(actual);
    int h = map_.size(), w = map_[0].size();
    std::vector<std::unique_ptr<Item>> items;
    for (int i = 0; i < 10; ++i) {
        auto it = ItemFactory::createRandomPotion();
        int x, y;
        do { x = std::rand()%w; y = std::rand()%h; } while (map_[y][x] != '.');
        it->setPosition(x,y); items.push_back(std::move(it));
    }
    for (int i = 0; i < 10; ++i) {
        auto it = ItemFactory::createRandomTreasure();
        int x, y;
        do { x = std::rand()%w; y = std::rand()%h; } while (map_[y][x] != '.');
        it->setPosition(x,y); items.push_back(std::move(it));
    }
    return items;
}

std::vector<std::unique_ptr<Enemy>> FloorGenerator::spawnEnemies(unsigned seed) const {
    unsigned actual = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    std::srand(actual);
    int h = map_.size(), w = map_[0].size();
    std::vector<std::unique_ptr<Enemy>> enemies;
    for (int i = 0; i < 20; ++i) {
        auto e = EnemyFactory::createRandomEnemy();
        int x, y;
        do { x = std::rand()%w; y = std::rand()%h; } while (map_[y][x] != '.');
        e->setPosition(x,y); enemies.push_back(std::move(e));
    }
    return enemies;
}

}
