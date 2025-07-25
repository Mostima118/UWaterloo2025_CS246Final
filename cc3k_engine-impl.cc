 module engine;
import <iostream>;
import <string>;
import <vector>;
import <memory>;
import <cstdlib>;
import <algorithm>;
import <numeric>;
import position;
import command;
import floor;
import playercharacter;
import playerfactory;
import itemfactory;
import character;

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
      //playerGold_{0},
      enhancementsEnabled_{false},   
      gameOver_{false},    
      isPreset{false}           
{}

std::string GameEngine::getRecentActionLog() const {
    if (actionLog_.empty()) return "No actions yet.";
    return actionLog_.back();  // or return all if needed
}
void GameEngine::spawnPlayer(FloorData &fd) {
    int h = fd.map.size(), w = fd.map[0].size();
    int x, y;
    do {
        x = std::rand() % w;
        y = std::rand() % h;
    } while (fd.map[y][x] != '.');
    player_ = PlayerFactory::createPlayer(raceCode_);
    player_->setPosition(x, y);
}
void GameEngine::setTile(int x, int y, char ch) {
    floors_[floorNum_ - 1].map[y][x] = ch;
}
void GameEngine::run() {
    bool replay;
    do {
        selectRace(); floors_.clear(); floorNum_=1;
        //no longer generate floor 1 info
        preGenerateFloors();
        if (!isPreset) {
            spawnPlayer(floors_[0]);
            {
                auto &fd0 = floors_[0];
                fd0.items   = floorGen_.spawnItems(seed_ + 0);
                fd0.enemies = floorGen_.spawnEnemies(seed_ + 0, fd0.items);
            }
        }
        // place player on first floor, not on stairs

        // MOVE RANDOM PLAYER GENERATION TO ALSO BE IN preGenerateFloors()
        
        
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

void GameEngine::preGenerateFloors() {
    Position commonStair;
    
    for (int i = 0; i < 5; ++i) {
        
        floorGen_.generateRandomFloor(seed_ + i);
        FloorData fd;
        if(floorGen_.hasPresetEntities()) {
            isPreset = true;
            player_ = floorGen_.spawnPresetPlayer();
            fd.enemies = floorGen_.spawnPresetEnemies();
            fd.items = floorGen_.spawnPresetItems();
            fd.stair = floorGen_.findPresetStairs();
            fd.map = floorGen_.getMap();
            fd.chambers = floorGen_.identifyChambers();

        } else {
            fd.map = floorGen_.getMap();
           
            std::srand(seed_ + i);
            // identify chambers once per floor
            fd.chambers = floorGen_.identifyChambers();
            if (i == 0) {
                // 1) Place PC first in a random chamber
                spawnPlayer(fd);
                auto pcPos = player_->getPosition();
                // find chamber index of PC
                int pcCh = -1;
                for (int ci = 0; ci < (int)fd.chambers.size(); ++ci) {
                    for (auto &p : fd.chambers[ci]) {
                        if (p == pcPos) { pcCh = ci; break; }
                    }
                    if (pcCh >= 0) break;
                }
                // 2) Choose stair in any other chamber
                int sx, sy;
                int chCount = fd.chambers.size();
                // --- changed: replaced do/while(false) with proper loop to avoid single iteration ---
                int targetCh;
                do {
                    targetCh = std::rand() % chCount;
                } while (targetCh == pcCh); // ensure targetCh != pcCh
                int idx = std::rand() % fd.chambers[targetCh].size();
                sx = fd.chambers[targetCh][idx].x;
                sy = fd.chambers[targetCh][idx].y;
                commonStair.x = sx;
                commonStair.y = sy;
            }
            fd.stair = commonStair;
            fd.map[commonStair.y][commonStair.x] = '/';
            fd.items   = floorGen_.spawnItems(seed_ + i);
            fd.enemies = floorGen_.spawnEnemies(seed_ + i, fd.items);
        
        }
        floors_.push_back(std::move(fd));
        
    }
    
}

Enemy* GameEngine::getTargetCharacter(Command cmd) {
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
            // CHANGE TO -> IF WRONG
            return e.get();  
        }
    }

    return nullptr;
}

Item* GameEngine::getTargetPotion(Command cmd) {
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
            return e.get();  // return pointer to the potion
        }
    }

    return nullptr;
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
    auto &fd = floors_[floorNum_ - 1];
    //check if currently stepping on dragon hoard, if yes then change status after move as dh is no longer being stepped on
    for (auto &e : fd.items) {
        //canCollect don't run if e is not DH
        if (e->isDragonHoard() && !(e->canCollect()) && e->getPosition() == pos) {
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
        default: break;
    }
    if (fd.map[pos.y][pos.x] == '.') return true;
    if (fd.map[pos.y][pos.x] == '+') return true;
    if (fd.map[pos.y][pos.x] == '#') return true;
    if (fd.map[pos.y][pos.x] == '/') return true;
    
    
    
    for (auto &e : fd.items) {
        //canCollect don't run if e is not DH
        if (e->isDragonHoard() && !(e->canCollect()) && e->getPosition() == pos) {
            e->changeStatus(); //change to being stepped on
            return true;             
        }
    }
    //dragon hoard already checked
    if (fd.map[pos.y][pos.x] != 'G') return true;
    return false;
}

void GameEngine::handleCommand(Command cmd) {
    auto &fd = floors_[floorNum_ - 1];

    // Movement commands
    if ((cmd >= Command::MoveNorth && cmd <= Command::MoveSW) && isValidMove(cmd)) {
        int dx, dy;
        switch (cmd) {
            case Command::MoveNorth: dx = 0; dy = -1; break;
            case Command::MoveSouth: dx = 0; dy = 1;  break;
            case Command::MoveEast:  dx = 1; dy = 0;  break;
            case Command::MoveWest:  dx = -1; dy = 0; break;
            case Command::MoveNE:    dx = 1; dy = -1; break;
            case Command::MoveNW:    dx = -1; dy = -1; break;
            case Command::MoveSE:    dx = 1; dy = 1;  break;
            case Command::MoveSW:    dx = -1; dy = 1; break;
            default: break;
        }
        Position oldPos = player_->getPosition();
        fd.setTile(oldPos.x, oldPos.y, '.'); // clear old position

        // Move player
        
        player_->setPosition( player_->getPosition().x + dx, player_->getPosition().y + dy );
        // After moving, check for stairs
        Position newPos = player_->getPosition();
        if (fd.map[newPos.y][newPos.x] == '/') {
            if (floorNum_ < (int)floors_.size()) {
                // go to next floor
                ++floorNum_;
                auto &newFd = floors_[floorNum_ - 1];
                // place player around the new floor's stair
                Position spawn = floorGen_.getRandomFreeNeighbor(newFd.map, newFd.stair);
                player_->setPosition(spawn.x, spawn.y);

                player_->resetPotions();
            }
        }else {
            fd.setTile(newPos.x, newPos.y, '@'); // mark new position
        }
        return;
    }

    // Attack commands
    if (cmd >= Command::AttackNorth && cmd <= Command::AttackSW) {
        player_->attackEffect(getTargetCharacter(cmd));
        return;
    }

    // Use Potion commands
    if (cmd >= Command::UsePotionNorth && cmd <= Command::UsePotionSW) {
        Item* potion = getTargetPotion(cmd);
        if (potion) {
            potion->See();
            player_->usePotion(potion->use());
            Position p = potion->getPosition();
            floorGen_.setTile(p.x, p.y, '.');

            // Remove it from item list
            auto &items = fd.items;
            for (auto it = items.begin(); it != items.end(); ++it) {
                if (it->get() == potion) {
                    items.erase(it);
                    break;
                }
            }
        }
        return;
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
            e->attackEffect(*player_);
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
            if((*it)->getType()=="Human") {
                fd.items.push_back(ItemFactory::createGold('H'));//createGold is for dead humans only
                fd.items.back()->setPosition((*it)->getPosition(.x, (*it)->getPosition().y)); //last item added
                floorGen_.setTile((*it)->getPosition().x, (*it)->getPosition().y, 'G');

            }else if((*it)->getType()=="Dragon") {
                Position ex = (*it)->getPosition();
                for (auto &e : fd.items) {
                    Position ep = e->getPosition();
                    if (ex == ep) {};
                }
                
            }else if((*it)->getType()=="Merchant") {
                if (!(*it)->isHostile()) (*it)->setHostile(true);
                   
                fd.items.push_back(ItemFactory::createGold('G'));  
                fd.items.back()->setPosition((*it)->getPosition().x, (*it)->getPosition().y); //last item added
                floorGen_.setTile((*it)->getPosition().x, (*it)->getPosition().y, 'G');  
                
            }else {
                player_->addGold((*it)->dropGold());
                floorGen_.setTile((*it)->getPosition().x, (*it)->getPosition().y, '.');
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
            if (!(*it)->isPotion() || ((*it)->isDragonHoard()&&(*it)->canCollect())) {
                player_->addGold((*it)->getValue());
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
  
}

//coloring not yet implemented, stats and action not yet implemented
// render
void GameEngine::render() const {
    const auto& fd = floors_[floorNum_- 1];
    const auto& map = fd.map;

    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            // Take in one tile each time, change color based on type
            char c = map[y][x];

            switch (c) {
                // 0 default, 30 black, 31 red, 32 green, 33 yellow, 34 blue, 35 purple
                case '@': case '#':
                    std::cout << "\033[1;34m"; break; // Player and Stairs - Blue
                case '0': case '1': case '2': case '3':
                case '4': case '5':
                    std::cout << "\033[1;32m"; break; // Potions - Green
                case '6':
                    std::cout << "\033[1;33m"; break; // Gold - Yellow
                case 'H': case 'W': case 'E':
                case 'O': case 'M': case 'D': case 'L':
                    std::cout << "\033[1;31m"; break; // Enemies - Red
                default:
                    std::cout << "\033[0m"; break; // Default
            }

            std::cout << c;
        }
        // Set back to default color after each row is printed, avoid the previous color being carried over
        std::cout << "\033[0m\n";
    }

    // Game stats
    std::cout << "\nRace: " << player_->getRace()
              << "   Gold: " << player_->getGold()
              // Not exactly the correct position, might have to revise this
              << "   Floor: " << floorNum_
              << "\n" << "HP: " << player_->getHP()
              << "\n" << "Atk: " << player_->getAtk()
              << "\n" << "Def: " << player_->getDef()
              << "\n" << "Action: " << getRecentActionLog()
              << std::endl;
}


int GameEngine::calculateScore() const {
    int sc=player_->getGold(); if(raceCode_=="s") sc=int(sc*1.5); return sc;
}

}
