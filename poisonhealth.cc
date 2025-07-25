export module poisonhealthpotion;

import <string>;

import potion;

// PH
export class PoisonHealthPotion : public Potion {
public:
    PoisonHealthPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};
