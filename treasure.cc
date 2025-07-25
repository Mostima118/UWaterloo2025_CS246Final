export module treasure;

import item;

import <string>;

export class Treasure : public Item {
protected:
    int value;

public:
    Treasure(int x, int y, int val);
    virtual ~Treasure();

    int getValue() override;

    // This returns the symbol of Gold: 'G'
    char getSymbol() const;

    // Returns a number character representing type:
    // '6' = NormalGold, '7' = SmallGold, '8' = MerchantHoard, '9' = DragonHoard
    char getType() override = 0;

    // Return false, treasure is not a potion
    bool isPotion() const override;

    virtual bool isDragonHoard() = 0;

    // For DragonHoard: only collectible when dragon is slain
    virtual bool canCollect() = 0;

    virtual void changeStatus () override = 0;

    virtual void changeCollectStatus () = 0;

    // Adds value to player; only implemented in leaf classes
    //  Returns the value of the gold
    virtual std::string use() override = 0;

    bool isSeen() override;

    void See() override;
};
