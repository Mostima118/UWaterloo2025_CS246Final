export module treasure;

import item;

import <string>;

export class Treasure : public Item {
protected:
    int value;

public:
    Treasure(int x, int y, int val);
    virtual ~Treasure() = default;

    int getValue() override;

    // This returns the symbol of Gold: 'G'
    char getSymbol() const;

    // Returns a number character representing type:
    // '6' = NormalGold, '7' = SmallGold, '8' = MerchantHoard, '9' = DragonHoard
    char getType() override = 0;

    // Return false, treasure is not a potion
    bool isPotion() const override;

    virtual bool isDragonHoard() const { return false; }

    // For DragonHoard: only collectible when dragon is slain
    virtual bool canCollect() = 0;

    virtual void changeStatus () override = 0;

    // Adds value to player; only implemented in leaf classes
    //  Returns the value of the gold
    virtual std::string use() override = 0;

    void See() override;
};

// Below are different types of treasure
export class NormalGold : public Treasure {
public:
    NormalGold(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
};

export class SmallGold : public Treasure {
public:
    SmallGold(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
};

export class MerchantHoard : public Treasure {
public:
    MerchantHoard(int x, int y);
    char getSymbol() const override;
    char getType() override;
    bool canCollect() override;
    std::string use() override;
    void changeStatus() override;
};

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
    void changeCollectStatus();

    bool isDragonHoard() const override { return true; }
    std::string use() override;

    // getStatus shows whether the hoard has been stepped on or not
    //  Returns status
    bool getStatus() const;

    // changeStatus change the status from true to false and vice versa
    void changeStatus() override;
};
