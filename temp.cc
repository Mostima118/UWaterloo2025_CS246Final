import <cctype>;

/*
// JUST USE ORIGINAL TO LOAD IN MAP
void FloorGenerator::loadPreset(const std::string &filename) {
    map_.clear();
    std::ifstream file(filename);

}
*/

// THEN CHECK IF THERE ARE PRESET ENTITIES, IF YES, RUN METHODS TO ADD THOSE ENTITES TO RESPECTIVE VECTORS
bool FloorGenerator::hasPresetEntites() {
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
                auto p = PlayerFactory::createPlayer("s"); // default just make shade??
                p->setPosition(x, y);
            }
        }
    }

    return p;
}

// MUST CALL THIS ONE FIRST BEFORE CALLING ITEMS SO CAN CHECK FOR HOARD FOR DRAGON!!
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


// FIX ENEMY AND OTHER BASE CLASSES TO HAVE VIRTUAL VERSIONS OF EXTRA FUNCTIONS IN SUBCLASSES SO CAN CALL :(


// NEED UPDATE COPY OF MAP USED IN ENGINE WITH NEW MAP WHERE NUMBERS REPLACED

// IF NO PRESETS, GENERATE RANDOM ENTITIES

