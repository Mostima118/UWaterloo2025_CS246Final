export module engine;
import <string>;
import <vector>;
import <memory>;
import <cstdlib>;
import position;
import command;
import floor;
import playercharacter;
import enemy;
import item;

namespace cc3k {

//struct Position { int x,y; };
bool operator==(const Position& a, const Position& b);
struct FloorData {
    std::vector<std::string> map;
    
    Position stair;
    std::vector<std::unique_ptr<Item>> items;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Chamber> chambers;  // CHANGED: store chambers here
};

export class GameEngine {
public:
    GameEngine(std::string layoutFile="", unsigned seed=0);
    void run();

private:
//added
    void detectNearbyPotions();
    std::vector<std::string> baseMap_;
    std::vector<std::vector<std::string>> actionLog_;
    std::string getRecentActionLog() const;

    Enemy* getTargetCharacter(Command cmd);
    Item* getTargetPotion(Command cmd);

    void setTile(int x, int y, char ch);
    bool isValidMove(Command cmd);

    void spawnPlayer(FloorData& fd);
    void updatePlayer();
    
    
    std::string layoutFile_;
    unsigned seed_;
    std::string raceCode_;
    int floorNum_;
    bool enhancementsEnabled_;
    bool gameOver_;
    bool isPreset;
    bool isStandingOnDH;
    bool isFreeze;
    CommandInterp interpreter_;
    FloorGenerator floorGen_;

    std::unique_ptr<PlayerCharacter> player_;



    std::vector<FloorData> floors_;

    void selectRace();
    void preGenerateFloors();
    bool processInput();
    void handleCommand(Command cmd);
    void updateState();
    void render() const;
    int calculateScore() const;

    void startNewTurn();
    void logAction(const std::string &msg);
    std::string getRecentTurnLog() const;
};

}
