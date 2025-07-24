export module floor;
import <string>;
import <vector>;
import <memory>;
import <queue>;
import item;
import enemy;
import playercharacter;

namespace cc3k {
export struct Position { int x; int y; };
export struct Chamber {
    std::vector<Position> tiles;
    bool contains(const Position &p) const {
        for (auto &t : tiles) if (t.x==p.x && t.y==p.y) return true;
        return false;
    }
};
export class FloorGenerator {
public:
    Position getRandomFreeNeighbor(const std::vector<std::string>& map, const Position& center) const;
    FloorGenerator() = default;
    void loadLayout(const std::string& filename);
    void generateRandomFloor(unsigned seed = 0);
    const std::vector<std::string>& getMap() const;
    //identifyChambers
    std::vector<Chamber> identifyChambers() const;
    void setTile(int x, int y, char ch);
    std::vector<std::unique_ptr<Item>> spawnItems(unsigned seed) const;
    std::vector<std::unique_ptr<Enemy>> spawnEnemies(unsigned seed) const;

    bool hasPresetEntities() const;
    std::unique_ptr<PlayerCharacter> spawnPresetPlayer();
    std::vector<std::unique_ptr<Enemy>> spawnPresetEnemies();
    std::vector<std::unique_ptr<Item>> spawnPresetItems();
};
private:
    std::vector<std::string> map_;
};
