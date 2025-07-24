module floor;
import <fstream>;
import <string>;
import <vector>;
import <cstdlib>;
import <ctime>;
import <cctype>;
import item;
import enemy;

namespace cc3k {

void FloorGenerator::loadLayout(const std::string& filename) {
    std::ifstream fin(filename);
    map_.clear(); std::string line;
    while (std::getline(fin, line)) map_.push_back(line);
}

bool FloorGenerator::hasPresetEntites() const {
    int h = map_.size();
    int w = map_[0].size();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (isalnum(c)) {
                return true;
            }

        }
    }
    return false;
}

std::unique_ptr<PlayerCharacter> FloorGenerator::spawnPresetPlayer() {
    int h = map_.size();
    int w = map_[0].size();
    for (int y= 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c == '@') {
                auto p = PlayerFactory::createPlayer("s"); // default just make shade
                p->setPosition(x, y);
            }
        }
    }

    return p;
}


std::vector<std::unique_ptr<Enemy>> FloorGenerator::spawnPresetEnemies() {
    std::vector<std::unique_ptr<Enemy>> enemies;
    int h = map_.size();
    int w = map_[0].size();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c == 'H' || c == 'W' || c == 'E' || c == 'O' || c == 'M' || c == 'D' || c == 'L') {
                auto e = EnemyFactory::createEnemy(c);
                e->setPosition(x, y);

                // if dragon, find its associated hoard
                if (e->getType() == "Dragon") {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            if (y + i >= 0 && y + i < h && x + j >= 0 && x + j < w) {
                                char temp = map_[y + i][x + j];
                                if (temp == '9') {
                                    e->setHoardPos(x + j, y + i);
                                }
                            }
                        }
                    }
                }

                enemies.push_back(std::move(e));
            }
        }
    }

    return enemies;
}

std::vector<std::unique_ptr<Item>> FloorGenerator::spawnPresetItems() {
    std::vector<std::unique_ptr<Item>> items;
    int h = map_.size();
    int w = map_[0].size();
    for (int y= 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c >= '0' && c <= '9') {
                auto i = ItemFactory::createPreset(c);
                i->setPosition(x, y);
                items.push_back(std::move(i));
                // update map, replace numbers with actual displayed symbols for player
                if (c <= '6') {
                    map_[y][x] = 'P';
                }
                else {
                    map_[y][x] = 'G';
                }
            }
        }
    }

    return items;
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