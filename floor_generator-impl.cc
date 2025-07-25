module floor;
import <fstream>;
import <string>;
import <vector>;
import <cstdlib>;
import <ctime>;
import <cctype>;
import <iostream>;
import item;
import enemy;
import position;
import playercharacter;
import playerfactory;
import enemyfactory;
import itemfactory;

namespace cc3k {
//settile
void FloorGenerator::setTile(int x, int y, char ch) { 
    map_[y][x] = ch; 
}
// get avaliable tile
Position FloorGenerator::getRandomFreeNeighbor(const std::vector<std::string>& map, const Position& center) const {
    std::vector<Position> candidates;
    int H = (int)map.size();
    int W = (int)map[0].size();
    // radius = 1
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dx == 0 && dy == 0) continue;
            int ny = center.y + dy;
            int nx = center.x + dx;
            if (ny >= 0 && ny < H && nx >= 0 && nx < W && map[ny][nx] == '.') {
                candidates.push_back({nx, ny});
            }
        }
    }
    if (!candidates.empty()) return candidates[std::rand() % candidates.size()];
    // radius = 2
    std::vector<Position> candidates2;
    for (int dy = -2; dy <= 2; ++dy) {
        for (int dx = -2; dx <= 2; ++dx) {
            if ((std::abs(dy) <= 1 && std::abs(dx) <= 1) || (dx == 0 && dy == 0)) continue;
            int ny = center.y + dy;
            int nx = center.x + dx;
            if (ny >= 0 && ny < H && nx >= 0 && nx < W && map[ny][nx] == '.') {
                candidates2.push_back({nx, ny});
            }
        }
    }
    if (!candidates2.empty()) return candidates2[std::rand() % candidates2.size()];
    return center;
}
void FloorGenerator::loadLayout(const std::string& filename) {
    std::ifstream fin(filename);
    map_.clear(); std::string line;
    while (std::getline(fin, line)) map_.push_back(line);
}

void FloorGenerator::generateRandomFloor(unsigned, std::string fileName) {
    loadLayout(fileName);
}

//new function: finish chamber initializing
std::vector<Chamber> FloorGenerator::identifyChambers() {
    int H = map_.size(), W = map_[0].size();
    std::vector<std::vector<bool>> seen(H, std::vector<bool>(W,false));
    std::vector<Chamber> chambers;
    //inb lambda function to check if tile is inside map
    auto inb=[&](int y,int x){return y>=0&&y<H&&x>=0&&x<W;};
    for(int y=0;y<H;++y) for(int x=0;x<W;++x) if(!seen[y][x]&&map_[y][x]=='.'){
        Chamber c;
        //create queue
        std::queue<Position>q;
        seen[y][x]=true;
        q.push({x,y});
        //go over every adjacent '.' until no more dots left
        while(!q.empty()){
            auto p=q.front();q.pop();
            c.tiles.push_back(p);
            static constexpr int dy[4]={1,-1,0,0},dx[4]={0,0,1,-1};
            for(int d=0;d<4;++d){
                int ny=p.y+dy[d], nx=p.x+dx[d];
                if(inb(ny,nx)&&!seen[ny][nx]&&map_[ny][nx]=='.'){
                    seen[ny][nx]=true;
                    q.push({nx,ny});
                }
            }
        }
        chambers.push_back(std::move(c));
    }
    return chambers;
}
const std::vector<std::string>& FloorGenerator::getMap() const {
    return map_;
}

bool FloorGenerator::hasPresetEntities() const {
    int h = map_.size();
    int w = map_[0].size();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];

            if (c != '.' && c != '+' && c != '#' && c != '\\' && c != '|' && c != '-' && c != ' ') {
                return true;
            }
        }
    }
    return false;
}

Position FloorGenerator::findPresetStairs() {
    int h = map_.size();
    int w = map_[0].size();
    for (int y= 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c == '\\') {
                Position p{x, y};
                return p;
            }
        }
    }
    return Position{0, 0};
}

Position FloorGenerator::findPlayerPreset() {
    int h = map_.size();
    int w = map_[0].size();
    for (int y= 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c == '@') {
                Position p{x, y};
                return p;
            }
        }
    }
    return Position{0, 0};
}

std::unique_ptr<PlayerCharacter> FloorGenerator::spawnPresetPlayer(std::string code) {
    int h = map_.size();
    int w = map_[0].size();
    for (int y= 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            if (c == '@') {
                auto p = PlayerFactory::createPlayer(code);
                p->setPosition(x, y);
                return p;
            }
        }
    }
    return nullptr;
}


std::vector<std::unique_ptr<Enemy>> FloorGenerator::spawnPresetEnemies() {
    std::vector<std::unique_ptr<Enemy>> enemies;
    int h = map_.size();
    int w = map_[0].size();
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            char c = map_[y][x];
            //changed to c style strchr
            if ( c == 'H' || c == 'W' || c == 'E' || c == 'O' || c == 'M' || c == 'D' || c == 'L' ) {
                auto e = EnemyFactory::createEnemy(c);
                e->setPosition(x, y);

                // if dragon, find its associated hoard
                if (e->getType() == "Dragon") {
                    for (int i = -1; i < 2; ++i) {
                        for (int j = -1; j < 2; ++j) {
                            if (y + i >= 0 && y + i < h && x + j >= 0 && x + j < w) {
                                char temp = map_[y + i][x + j];
                                if (temp == '9') {
                                    e->setHoardPos(Position{x + j, y + i});
                                }
                            }
                        }
                    }
                }
                enemies.push_back(std::move(e));
                setTile(x, y, enemies.back()->getSymbol());
            }
        }
    }
    return enemies;
}
std::vector<std::unique_ptr<Item>> FloorGenerator::spawnPresetItems() {
    std::vector<std::unique_ptr<Item>> items;
    for (int y = 0; y < (int)map_.size(); ++y) for (int x = 0; x < (int)map_[0].size(); ++x) {
        char c = map_[y][x];
        if (c >= '0' && c <= '9') {
            auto it = ItemFactory::createPreset(c);
            it->setPosition(x, y);
            items.push_back(std::move(it));
            // update map, replace numbers with actual displayed symbols for player
            setTile(x, y, items.back()->getSymbol());
        }
    }
    return items;
}


std::vector<std::unique_ptr<Item>> FloorGenerator::spawnItems(unsigned seed) {
    unsigned s = seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed;
    std::srand(s);
    auto chambers = identifyChambers();
    std::vector<std::unique_ptr<Item>> items;

    // Spawn 10 random potions
    for (int i = 0; i < 10; ++i) {
        auto potion = ItemFactory::createRandomPotion();
        Position pos;
        do {
            auto &chamber = chambers[std::rand() % chambers.size()];
            pos = chamber.tiles[std::rand() % chamber.tiles.size()];
        } while (map_[pos.y][pos.x] != '.');
        setTile(pos.x, pos.y, potion->getSymbol());
        potion->setPosition(pos.x, pos.y);
        items.push_back(std::move(potion));
    }

    // Spawn 10 random treasures
    for (int i = 0; i < 10; ++i) {
        auto treasure = ItemFactory::createRandomTreasure();
        Position pos;
        do {
            auto &chamber = chambers[std::rand() % chambers.size()];
            pos = chamber.tiles[std::rand() % chamber.tiles.size()];
        } while (map_[pos.y][pos.x] != '.');
        setTile(pos.x, pos.y, treasure->getSymbol());
        treasure->setPosition(pos.x, pos.y);
        items.push_back(std::move(treasure));
    }

    return items;
}

std::vector<std::unique_ptr<Enemy>> FloorGenerator::spawnEnemies(unsigned seed, const std::vector<std::unique_ptr<Item>>& items) {
    unsigned s = (seed == 0 ? static_cast<unsigned>(std::time(nullptr)) : seed);
    std::srand(s);

    auto chambers = identifyChambers();
    std::vector<std::unique_ptr<Enemy>> enemies;
    int C = chambers.size();

    // Dragon spawns
    for (auto &it : items) {
        if (it->isDragonHoard()) {
            Position hoard = it->getPosition();
            auto d = EnemyFactory::createEnemy('D');
            d->setHoardPos(hoard);
            Position spawn = getRandomFreeNeighbor(map_, hoard);
            d->setPosition(spawn.x, spawn.y);
            setTile(spawn.x, spawn.y, d->getSymbol());
            enemies.push_back(std::move(d));
        }
    }

    // 20 other random enemies
    for (int i = 0; i < 20; ++i) {
        auto e = EnemyFactory::createRandomEnemy();
        Position pos;
        do {
            auto &chamber = chambers[std::rand() % C];
            pos = chamber.tiles[std::rand() % chamber.tiles.size()];
        } while (map_[pos.y][pos.x] != '.');
        e->setPosition(pos.x, pos.y);
        setTile(pos.x, pos.y, e->getSymbol());
        enemies.push_back(std::move(e));
    }

    return enemies;
}

}
