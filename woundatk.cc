export module woundatkpotion;

import <string>;

import potion;

// WA
export class WoundAtkPotion : public Potion {
public:
    WoundAtkPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};
