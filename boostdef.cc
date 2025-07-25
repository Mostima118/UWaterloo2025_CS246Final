export module boostdefpotion;

import <string>;

import potion;

// BD
export class BoostDefPotion : public Potion {
public:
    BoostDefPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};
