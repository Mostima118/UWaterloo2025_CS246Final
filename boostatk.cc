export module boostatkpotion;

import <string>;

import potion;

// BA
export class BoostAtkPotion : public Potion {
public:
    BoostAtkPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};