export module floor;
import <string>;
import <vector>;
import <memory>;
import item;
import enemy;
import playercharacter;

namespace cc3k {

export class FloorGenerator {
public:
    FloorGenerator() = default;
    void loadLayout(const std::string& filename);
    void generateRandomFloor(unsigned seed = 0);
    const std::vector<std::string>& getMap() const;
    std::vector<std::unique_ptr<Item>> spawnItems(unsigned seed) const;
    std::vector<std::unique_ptr<Enemy>> spawnEnemies(unsigned seed) const;

    bool hasPresetEntities() const;
    std::unique_ptr<PlayerCharacter> spawnPresetPlayer();
    std::vector<std::unique_ptr<Enemy>> FloorGenerator::spawnPresetEnemies();
    std::vector<std::unique_ptr<Item>> FloorGenerator::spawnPresetItems();
    
};
private:
    std::vector<std::string> map_;
};
