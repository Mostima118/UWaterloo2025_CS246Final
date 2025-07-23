//coloring not yet implemented, stats and action not yet implemented
// This is the original function
void GameEngine::render() const {
    const auto &fd=floors_[floorNum_-1];
    for(const auto &row:fd.map) std::cout<<row<<"\n";
    std::cout<<"Gold: "<<playerGold_<<"  Score: "<<calculateScore()<<"\n";
}



// render
void GameEngine::render() const {
    const auto& fd = floors_[floorNum_];
    const auto& map = fd.map;

    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            // Take in one tile each time, change color based on type
            char c = map[y][x];

            switch (c) {
                // 0 default, 30 black, 31 red, 32 green, 33 yellow, 34 blue, 35 purple
                case '@': case '#':
                    std::cout << "\033[1;34m"; break; // Player and Stairs - Blue
                case '0': case '1': case '2': case '3':
                case '4': case '5':
                    std::cout << "\033[1;32m"; break; // Potions - Green
                case '6':
                    std::cout << "\033[1;33m"; break; // Gold - Yellow
                case 'H': case 'W': case 'E':
                case 'O': case 'M': case 'D': case 'L':
                    std::cout << "\033[1;31m"; break; // Enemies - Red
                default:
                    std::cout << "\033[0m"; break; // Default
            }

            std::cout << c;
        }
        // Set back to default color after each row is printed, avoid the previous color being carried over
        std::cout << "\033[0m\n";
    }

    // Game stats
    std::cout << "\nRace: " << player_->getRaceCode()
              << "   Gold: " << playerGold_
              // Not exactly the correct position, might have to revise this
              << "   Floor: " << floorNum_ + 1
              << "\n" << "HP: " << player_->getHP()
              << "\n" << "Atk: " << player_->getAtk()
              << "\n" << "Def: " << player_->getDef()
              << "\n" << "Action: " << player_->getActionLog()
              // Might want to modify the above player function name based on the player class
              << std::endl;
}
