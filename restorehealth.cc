export module restorehealthpotion;

import <string>;

import potion;

export class RestoreHealthPotion : public Potion {
public:
    RestoreHealthPotion(int x, int y);
    char getSymbol() const override;
    std::string use() override;
    char getType() override;
    bool isDragonHoard() override;
};
