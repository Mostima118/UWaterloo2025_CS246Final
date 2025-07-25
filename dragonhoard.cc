export module dragonhoard;

import item;
import treasure;

import <string>;

export class DragonHoard : public Treasure {
private:
    bool status;          // Status for stepping on the hoard
    bool collectStatus;   // Status for collecting the hoard
public:
    DragonHoard(int x, int y, bool alive = true);
    char getSymbol() const override;
    char getType() override;

    // Returns the collectStatus
    bool canCollect() override;

    // changeCollectStatus changes the collectStatus
    void changeCollectStatus() override;

    bool isDragonHoard() override;
    std::string use() override;

    // getStatus shows whether the hoard has been stepped on or not
    //  Returns status
    bool getStatus() const;

    // changeStatus change the status from true to false and vice versa
    void changeStatus() override;
};
