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
    void loadLayout(const std::string& filename);
    void generateRandomFloor(unsigned seed = 0);
    const std::vector<std::string>& getMap() const;
    std::vector<std::unique_ptr<Item>> spawnItems(unsigned seed) const;
    std::vector<std::unique_ptr<Enemy>> spawnEnemies(unsigned seed) const;
};
private:
    std::vector<std::string> map_;
};
