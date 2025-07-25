export module merchanthoard;

import item;
import treasure;

import <string>;

export class MerchantHoard : public Treasure {
public:
    MerchantHoard(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
    bool isDragonHoard() override;
    void changeCollectStatus() override;
};
