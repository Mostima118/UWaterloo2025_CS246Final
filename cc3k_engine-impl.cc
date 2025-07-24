module engine;
import <iostream>;
import <string>;
import <vector>;
import <memory>;
import <cstdlib>;
import <algorithm>;
import <numeric>;
import command;
import floor;
import player;
import enemy;
import item;

namespace cc3k {
bool operator==(const Position& a, const Position& b) {
    return a.x == b.x && a.y == b.y;
}
GameEngine::GameEngine(std::string layoutFile, unsigned seed)
    : layoutFile_{std::move(layoutFile)},
      seed_{seed},
      floorNum_{1},
      playerGold_{0},
      enhancementsEnabled_{false},   
      gameOver_{false}               
{}

void GameEngine::run() {
    bool replay;
    do {
        selectRace(); floors_.clear(); floorNum_=1;
        preGenerateFloors();
        // place player on first floor, not on stairs

        // MOVE RANDOM PLAYER GENERATION TO ALSO BE IN preGenerateFloors()
        { auto &fd=floors_[0]; int h=fd.map.size(), w=fd.map[0].size();
          player_=PlayerFactory::createPlayer(raceCode_);
          int x,y; std::srand(seed_);
          do { x=std::rand()%w; y=std::rand()%h; }
          while (fd.map[y][x] != '.' || (x==fd.upStair.x&&y==fd.upStair.y));
          player_->setPosition(x,y);
        }
        
        while (true) {
            render(); 
            if(processInput()) break; //input processed
            updateState(); 
        }
        std::cout<<"Game over! Score: "<<calculateScore()<<"\n";
        std::cout<<"Play again? (y/n): "; std::string ans; std::getline(std::cin,ans);
        replay = !ans.empty()&&(ans[0]=='y'||ans[0]=='Y');
    } while (replay);
}

void GameEngine::selectRace() {
    raceCode_.clear();
    while (raceCode_.empty()) {
        std::cout<<"Choose race (s/d/v/t/g) or q to quit: ";
        std::string in; if(!std::getline(std::cin,in)) std::exit(0);
        Command c=interpreter_.parse(in);
        switch(c){case Command::SelectShade: raceCode_="s";break;
        case Command::SelectDrow: raceCode_="d";break;
        case Command::SelectVampire: raceCode_="v";break;
        case Command::SelectTroll: raceCode_="t";break;
        case Command::SelectGoblin: raceCode_="g";break;
        case Command::Quit: std::exit(0);
        default: std::cout<<"Invalid\n";}
    }
}

// here made change: instead of using "/" for stairs, we use "<" to indicate up and ">" to indicate down
void GameEngine::preGenerateFloors() {
    Position nextUp;              // will hold where the next floor’s '<' goes

    for (int i = 0; i < 5; ++i) {
        floorGen_.generateRandomFloor(seed_ + i);
        FloorData fd;

        if (floorGen_.hasPresetEntities()) {
            player_ = floorGen_.spawnPresetPlayer();
            fd.enemies = floorGen_.spawnPresetEnemies();
            fd.items = floorGen_.spawnPresetItems();
            fd.map = floorGen.getMap(); // last here because spawnPresetItems changes map

            // FIX STAIRS LATER - NEED ANOTHER METHOD TO FIND STAIRS AND PUT INTO FLOOR DATA
            // AND MAKE FLOOR DATA ONLY HOLD LOCATION OF STAIRS DOWN

        }
        else {
            // so also need to fix stairs logic here
            // also have player character generation here to have correct order

            fd.map = floorGen_.getMap();
            int h = fd.map.size(), w = fd.map[0].size();
            std::srand(seed_ + i);

            // 1) Place the up-stair for floor i (except floor 1)
            if (i > 0) {
                fd.upStair = nextUp;
                fd.map[fd.upStair.y][fd.upStair.x] = '<';
            }

            // 2) Place the down-stair for floor i (except floor 5)
            if (i < 4) {
                int x, y;
                do {
                    x = std::rand() % w;
                    y = std::rand() % h;
                } while (fd.map[y][x] != '.');
                fd.downStair = {x, y};
                fd.map[y][x] = '>';
                nextUp = fd.downStair;    // carry this forward as next floor’s up-stair
            }

            // 3) Spawn items and enemies in the remaining '.' tiles
            fd.items   = floorGen_.spawnItems(seed_ + i);
            fd.enemies = floorGen_.spawnEnemies(seed_ + i);

        }

        floors_.push_back(std::move(fd));
    }
}

bool GameEngine::processInput() {
    std::cout<<"> "; std::string in;
    if(!std::getline(std::cin,in)) return true;
    Command c=interpreter_.parse(in);
    if(c==Command::Quit||c==Command::Restart) return true;
    //for dlc
    if(c==Command::ToggleEnhancements){enhancementsEnabled_=!enhancementsEnabled_;return false;}
    // block mid-game race
    if( c == Command::SelectShade ||
        c == Command::SelectDrow ||
        c == Command::SelectVampire ||
        c == Command::SelectTroll || 
        c == Command::SelectGoblin){
        std::cout<<"Cannot change race mid-game\n"; return false;
    }
    handleCommand(c); return false;
}

void GameEngine::handleCommand(Command cmd) {
    auto &fd = floors_[floorNum_-1]; auto pos=player_->getPosition();
    switch(cmd) {
        case Command::MoveNorth: player_->move(0,-1); break;
        case Command::MoveSouth: player_->move(0,1);  break;
        case Command::MoveEast:  player_->move(1,0);  break;
        case Command::MoveWest:  player_->move(-1,0); break;
        case Command::MoveNE:    player_->move(1,-1); break;
        case Command::MoveNW:    player_->move(-1,-1);break;
        case Command::MoveSE:    player_->move(1,1);  break;
        case Command::MoveSW:    player_->move(-1,1); break;
        case Command::UpStairs:
            if(pos.x==fd.upStair.x&&pos.y==fd.upStair.y&&floorNum_>1) {
                floorNum_--; player_->setPosition(floors_[floorNum_-1].downStair);
            }
            break;
        case Command::DownStairs:
            if(pos.x==fd.downStair.x&&pos.y==fd.downStair.y&&floorNum_<5) {
                floorNum_++; player_->setPosition(floors_[floorNum_-1].upStair);
            }
            break;
        case Command::UsePotionNorth: player_->usePotion(Direction::North);   break;
        case Command::UsePotionSouth: player_->usePotion(Direction::South);   break;
        case Command::UsePotionEast:  player_->usePotion(Direction::East);    break;
        case Command::UsePotionWest:  player_->usePotion(Direction::West);    break;
        case Command::AttackNorth:    player_->attack(Direction::North);      break;
        case Command::AttackSouth:    player_->attack(Direction::South);      break;
        case Command::AttackEast:     player_->attack(Direction::East);       break;
        case Command::AttackWest:     player_->attack(Direction::West);       break;
        default: break;
    }
}
//enemy retaliation, move enemy, clean up ... etc
void GameEngine::updateState() {
    // 1) Get PC info after player input    

    auto pos = player_->getPosition();
    auto &fd = floors_[floorNum_ - 1];

    // 2) Enemy retaliation: any adjacent, alive enemy attacks the player
    for (auto &e : fd.enemies) {
        Position ep = e->getPosition();
        int dx = std::abs(ep.x - pos.x);
        int dy = std::abs(ep.y - pos.y);
        if ((dx <= 1 && dy <= 1) && (dx != 0 || dy != 0) && e->isAlive()) {
            e->attack(*player_);
        }
    }

    // 3) Move all non-dragon enemies, one pass row-by-row
    auto &enemies = fd.enemies;
    std::vector<size_t> order(enemies.size());
    std::iota(order.begin(), order.end(), 0);
    std::sort(order.begin(), order.end(), [&](size_t a, size_t b) {
        auto pa = enemies[a]->getPosition();
        auto pb = enemies[b]->getPosition();
        return (pa.y < pb.y) || (pa.y == pb.y && pa.x < pb.x);
    });

    std::vector<bool> moved(enemies.size(), false);
    static constexpr int dxs[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    static constexpr int dys[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    for (size_t idx : order) {
        auto &e = enemies[idx];
        if (e->getType() == EnemyType::Dragon || moved[idx]) continue;

        Position cur = e->getPosition();
        std::vector<Position> cand;
        for (int d = 0; d < 8; ++d) {
            Position np{ cur.x + dxs[d], cur.y + dys[d] };
            // bounds and walkable check
            if (np.y < 0 || np.y >= (int)fd.map.size() ||
                np.x < 0 || np.x >= (int)fd.map[0].size()) continue;
            if (fd.map[np.y][np.x] != '.') continue;
            // not occupied by another enemy or the player
            bool occ = false;
            for (auto &o : enemies)
                if (o.get() != e.get() && o->getPosition() == np) { occ = true; break; }
            if (occ || player_->getPosition() == np) continue;
            cand.push_back(np);
        }
        if (cand.empty()) continue;
        Position dest = cand[std::rand() % cand.size()];
        e->setPosition(dest.x, dest.y);
        moved[idx] = true;
    }

    // 4) Cleanup dead enemies & collect their gold
    for (auto it = fd.enemies.begin(); it != fd.enemies.end();) {
        if (!(*it)->isAlive()) {
            playerGold_ += (*it)->dropGold();
            it = fd.enemies.erase(it);
        } else {
            ++it;
        }
    }

    // 5) Item pickups
    for (auto it = fd.items.begin(); it != fd.items.end();) {
        if ((*it)->getPosition() == player_->getPosition()) {
            if ((*it)->isPotion())
                player_->applyPotion(static_cast<Potion&>(**it));
            else
                playerGold_ += (*it)->getValue();
            it = fd.items.erase(it);
        } else {
            ++it;
        }
    }

    // 6) Check player death
    if (!player_->isAlive()) {
        gameOver_ = true;
    }

    // 7) Mid-turn stair handling (just in case)
    pos = player_->getPosition();
    if (pos == fd.downStair && floorNum_ < (int)floors_.size()) {
        floorNum_++;
        player_->setPosition(floors_[floorNum_ - 1].upStair);
    } else if (pos == fd.upStair && floorNum_ > 1) {
        floorNum_--;
        player_->setPosition(floors_[floorNum_ - 1].downStair);
    }
}

//coloring not yet implemented, stats and action not yet implemented
void GameEngine::render() const {
    const auto &fd=floors_[floorNum_-1];
    for(const auto &row:fd.map) std::cout<<row<<"\n";
    std::cout<<"Gold: "<<playerGold_<<"  Score: "<<calculateScore()<<"\n";
}

int GameEngine::calculateScore() const {
    int sc=playerGold_; if(raceCode_=="s") sc=int(sc*1.5); return sc;
}

}