export module enemyfactory;
import enemy;
import <memory>;

export class EnemyFactory {
 public:
    static std::unique_ptr<Enemy> createRandomEnemy();
    static std::unique_ptr<Enemy> createEnemy(const char &type);
};
