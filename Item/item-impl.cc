module item;

Item::Item(int row, int col, ItemType type) : row{row}, col{col}, type{type} {}

int Item::getRow() const { return row; }
int Item::getCol() const { return col; }
ItemType Item::getType() const { return type; }
