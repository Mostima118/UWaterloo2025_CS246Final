export module floor;
import <string>;
import <vector>;
import <memory>;
import item;
import enemy;

namespace cc3k {

export class FloorGenerator {
public:
    FloorGenerator() = default;
    //load layout from file(base layout)
    void loadLayout(const std::string& filename);
    //generate randomfloor (do not support turn on/off in case of pre-rendered maps)
    void generateRandomFloor(unsigned seed = 0);
    //getMap()
    const std::vector<std::string>& getMap() const;
    //item spawn
    std::vector<std::unique_ptr<Item>> spawnItems(unsigned seed) const;
    //enemy spawn
    std::vector<std::unique_ptr<Enemy>> spawnEnemies(unsigned seed) const;
};
private:
    std::vector<std::string> map_;
};
