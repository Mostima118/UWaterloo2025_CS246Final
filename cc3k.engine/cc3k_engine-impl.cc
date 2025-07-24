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
void setTile(int x, int y, char ch) {
    map_[y][x] = ch;
}
void GameEngine::run() {
    bool replay;
    do {
        selectRace(); floors_.clear(); floorNum_=1;
        
        preGenerateFloors();
        // place player on first floor, not on stairs
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
        fd.enemies = floorGen_.spawnEnemies(seed_ + i, fd.items);

        floors_.push_back(std::move(fd));
    }
}

Character* GameEngine::getTargetCharacter(Command cmd) {
    auto &fd = floors_[floorNum_ - 1];
    Position pcPos = player_->getPosition();
    int dx = 0, dy = 0;

    switch (cmd) {
        case Command::AttackNorth: dy = -1; break;
        case Command::AttackSouth: dy = 1;  break;
        case Command::AttackEast:  dx = 1;  break;
        case Command::AttackWest:  dx = -1; break;
        case Command::AttackNE:    dx = 1; dy = -1; break;
        case Command::AttackNW:    dx = -1; dy = -1; break;
        case Command::AttackSE:    dx = 1; dy = 1; break;
        case Command::AttackSW:    dx = -1; dy = 1; break;
        default: return nullptr;
    }

    Position targetPos{pcPos.x + dx, pcPos.y + dy};

    for (auto &e : fd.enemies) {
        if (e->isAlive() && e->getPosition() == targetPos) {
            return e.get();  
        }
    }

    return nullptr;
}
std::string GameEngine::getTargetPotion(Command cmd) {
    auto &fd = floors_[floorNum_ - 1];
    Position pcPos = player_->getPosition();
    int dx = 0, dy = 0;

    switch (cmd) {
        case Command::UsePotionNorth: dy = -1; break;
        case Command::UsePotionSouth: dy = 1;  break;
        case Command::UsePotionEast:  dx = 1;  break;
        case Command::UsePotionWest:  dx = -1; break;
        case Command::UsePotionNE:    dx = 1; dy = -1; break;
        case Command::UsePotionNW:    dx = -1; dy = -1; break;
        case Command::UsePotionSE:    dx = 1; dy = 1; break;
        case Command::UsePotionSW:    dx = -1; dy = 1; break;
        default: return nullptr;
    }

    Position targetPos{pcPos.x + dx, pcPos.y + dy};

    for (auto &e : fd.items) {
        if (e->isPotion() && e->getPosition() == targetPos) {
            return e.use();  
        }
    }

    return "null";
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
bool GameEngine::isValidMove(Command cmd) {
    auto pos=player_->getPosition();
    //check if currently stepping on dragon hoard, if yes then change status after move as dh is no longer being stepped on
    for (auto &e : fd.items) {
        //canCollect don't run if e is not DH
        if (e->isDragonHoard() && e->!canCollect() && e->getPosition() == pos) {
            e->changeStatus();          
        }
    }
    switch(cmd) {
        case Command::MoveNorth: --pos.y; break;
        case Command::MoveSouth: ++pos.y;  break;
        case Command::MoveEast:  ++pos.x;  break;
        case Command::MoveWest:  --pos.x; break;
        case Command::MoveNE:    --pos.y; ++pos.x; break;
        case Command::MoveNW:    --pos.y; --pos.x;break;
        case Command::MoveSE:    ++pos.y; ++pos.x;  break;
        case Command::MoveSW:    ++pos.y; --pos.x; break;
    }
    if (fd.map[pos.y][pos.x] == '.') return true;
    if (fd.map[pos.y][pos.x] == '+') return true;
    if (fd.map[pos.y][pos.x] == '#') return true;
    if (fd.map[pos.y][pos.x] == '<') return true;
    if (fd.map[pos.y][pos.x] == '>') return true;
    
    auto &fd = floors_[floorNum_ - 1];
    for (auto &e : fd.items) {
        //canCollect don't run if e is not DH
        if (e->isDragonHoard() && !e->canCollect() && e->getPosition() == pos) {
            e->changeStatus(); //change to being stepped on
            return true;             
        }
    }
    //dragon hoard already checked
    if (fd.map[pos.y][pos.x] != 'G') return true;
    return false;
}
void GameEngine::handleCommand(Command cmd) {
    auto &fd = floors_[floorNum_-1]; auto pos=player_->getPosition();
    if((cmd == Command::MoveNorth ||
        cmd == Command::MoveSouth ||
        cmd == Command::MoveEast ||
        cmd == Command::MoveWest ||
        cmd == Command::MoveNE ||
        cmd == Command::MoveNW ||
        cmd == Command::MoveSE ||
        cmd == Command::MoveSW) && isValidMove(cmd)) {
            switch(cmd) {
                case Command::MoveNorth: player_->move(0,-1); break;
                case Command::MoveSouth: player_->move(0,1);  break;
                case Command::MoveEast:  player_->move(1,0);  break;
                case Command::MoveWest:  player_->move(-1,0); break;
                case Command::MoveNE:    player_->move(1,-1); break;
                case Command::MoveNW:    player_->move(-1,-1);break;
                case Command::MoveSE:    player_->move(1,1);  break;
                case Command::MoveSW:    player_->move(-1,1); break;
            }
    }
    switch(cmd) {
        case Command::UpStairs:
            if(pos.x==fd.upStair.x&&pos.y==fd.upStair.y&&floorNum_>1) {
                floorNum_--; player_->setPosition(floors_[floorNum_-1].downStair);
                player_->resetPotion();
            }
            break;
        case Command::DownStairs:
            if(pos.x==fd.downStair.x&&pos.y==fd.downStair.y&&floorNum_<5) {
                floorNum_++; player_->setPosition(floors_[floorNum_-1].upStair);
                player_->resetPotion();
            }
            break;
        case Command::AttackNorth: player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackSouth: player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackEast:  player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackWest:  player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackNE:    player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackNW:    player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackSE:    player_->attack(getTargetCharacter(cmd)); break;
        case Command::AttackSW:    player_->attack(getTargetCharacter(cmd)); break;
        default: player_->usePotion(getTargetPotion(cmd)); break;
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
        if (e->getType() == "Dragon" || moved[idx]) continue;

        Position cur = e->getPosition();
        std::vector<Position> cand;
        for (int d = 0; d < 8; ++d) {
            Position np{ cur.x + dxs[d], cur.y + dys[d] };
            // bounds and walkable check
            if (np.y < 0 || np.y >= (int)fd.map.size() ||
                np.x < 0 || np.x >= (int)fd.map[0].size()) continue;
            if (fd.map[np.y][np.x] != '.') continue;
            
            cand.push_back(np);
        }
        if (cand.empty()) continue;
        floorGen_.setTile(cur.x, cur.y, '.'); //return to '.'
        Position dest = cand[std::rand() % cand.size()];
        floorGen_.setTile(dest.x, dest.y, e->getSymbol()); //set to enemy symbol
        e->setPosition(dest.x, dest.y);
        moved[idx] = true;
    }

    // 4) Cleanup dead enemies & collect their gold
    for (auto it = fd.enemies.begin(); it != fd.enemies.end();) {
        if (!(*it)->isAlive()) {
            switch((*it)->getType()) {
                case "Human":
                    items.push_back(ItemFactory::createGold('H'));//createGold is for dead humans only
                    items.back()->setPosition(p.x, p.y); //last item added
                    floorGen_.setTile(p.x, p.y, 'G');
                    break;
                case "Dragon":
                    Position ex = (*it)->getPosition();
                    for (auto &e : fd.items) {
                        Position ep = e->getPosition();
                        if (ex == ep) {};
                    }
                    break;
                case "Merchant":
                    if (!isHostile) (*it)->setHostile();
                    floorGen_.setTile(p.x, p.y, 'G');
                    items.push_back(ItemFactory::createGold('G'));                 
                    break;
                default:
                // 3) Otherwise add gold directly
                    playerGold_ += (*it)->dropGold();
                    floorGen_.setTile(p.x, p.y, '.');
                break;
            }
            it = fd.enemies.erase(it);
        } else {
            ++it;
        }
    }

    // 5) Item pickups
    for (auto it = fd.items.begin(); it != fd.items.end();) {
        if ((*it)->getPosition() == player_->getPosition()) {
            //dragonHoard
            if ((*it)->isGold() || ((*it)->isDragonHoard()&&(*it)->canCollect())) {
                playerGold_ += (*it)->getValue();
                floorGen_.setTile( (*it)->getPosition().x, (*it)->getPosition().y, '.' ); // calls setTile with '.' char
                it = fd.items.erase(it); 
            }
        } else {
            ++it;
        }
    }

    // 6) Check player death
    if (!player_->isAlive()) {
        gameOver_ = true;
    }
    /*
    // 7) Mid-turn stair handling (just in case)
    pos = player_->getPosition();
    if (pos == fd.downStair && floorNum_ < (int)floors_.size()) {
        floorNum_++;
        player_->setPosition(floors_[floorNum_ - 1].upStair);
        player_->resetPotion();
    } else if (pos == fd.upStair && floorNum_ > 1) {
        floorNum_--;
        player_->setPosition(floors_[floorNum_ - 1].downStair);
        player_->resetPotion();
    }
        */
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