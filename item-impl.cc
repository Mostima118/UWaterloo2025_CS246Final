module item;

import <cstdlib>;
import <memory>;
import <vector>;
import position;

Item::Item(int x, int y) : x{x}, y{y}, p{x, y} {}

int Item::getX() const { return x; }
int Item::getY() const { return y; }

Position Item::getPosition() { return p; }
