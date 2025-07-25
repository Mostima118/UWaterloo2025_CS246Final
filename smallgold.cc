export module smallgold;

import item;
import treasure;

import <string>;

export class SmallGold : public Treasure {
public:
    SmallGold(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
    bool isDragonHoard() override;
    void changeCollectStatus() override;
};
