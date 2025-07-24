export module engine;
import <string>;
import <vector>;
import <memory>;
import <cstdlib>;
import command;
import floor;
import player;
import enemy;
import item;

namespace cc3k {

struct Position { int x,y; };
bool operator==(const Position& a, const Position& b) {}
struct FloorData {
    std::vector<std::string> map;
    Position stairs;

    std::vector<std::unique_ptr<Item>> items;
    std::vector<std::unique_ptr<Enemy>> enemies;
};

export class GameEngine {
public:
    GameEngine(std::string layoutFile="", unsigned seed=0);
    void run();

private:

    std::string layoutFile_;
    unsigned seed_;
    std::string raceCode_;
    int floorNum_;
    bool gameOver_;

    CommandInterp interpreter_;
    FloorGenerator floorGen_;

    std::unique_ptr<Player> player_;
    int playerGold_;
    bool enhancementsEnabled_;

    std::vector<FloorData> floors_;

    void selectRace();
    void preGenerateFloors();
    bool processInput();
    void handleCommand(Command cmd);
    void updateState();
    void render() const;
    int calculateScore() const;
};

}