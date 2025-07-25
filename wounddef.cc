export module wounddefpotion;

import <string>;

import potion;

// WD
export class WoundDefPotion : public Potion {
public:
    WoundDefPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};
