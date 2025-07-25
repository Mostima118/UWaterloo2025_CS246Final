export module normalgold;

import item;
import treasure;

import <string>;

// Below are different types of treasure
export class NormalGold : public Treasure {
public:
    NormalGold(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
    bool isDragonHoard() override;
    void changeCollectStatus() override;
};
