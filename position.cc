export module position;

export struct Position {
  int x, y;
  Position(): x{0}, y{0} {}
  Position(int x, int y): x{x}, y{y} {}
};
