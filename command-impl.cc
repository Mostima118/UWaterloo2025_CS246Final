module command;
import <string>;

namespace cc3k{
Command CommandInterp::parse(const std::string& cmd) const {
    // race selection
    if (cmd == "s") return Command::SelectShade;
    if (cmd == "d") return Command::SelectDrow;
    if (cmd == "v") return Command::SelectVampire;
    if (cmd == "t") return Command::SelectTroll;
    if (cmd == "g") return Command::SelectGoblin;
    // movement
    if (cmd == "no" || cmd == "north")      return Command::MoveNorth;
    if (cmd == "so" || cmd == "south")      return Command::MoveSouth;
    if (cmd == "ea" || cmd == "east")       return Command::MoveEast;
    if (cmd == "we" || cmd == "west")       return Command::MoveWest;
    if (cmd == "ne")                         return Command::MoveNE;
    if (cmd == "nw")                         return Command::MoveNW;
    if (cmd == "se")                         return Command::MoveSE;
    if (cmd == "sw")                         return Command::MoveSW;
    // potion use
    if (cmd == "u no")                       return Command::UsePotionNorth;
    if (cmd == "u so")                       return Command::UsePotionSouth;
    if (cmd == "u ea")                       return Command::UsePotionEast;
    if (cmd == "u we")                       return Command::UsePotionWest;
    if (cmd == "u ne")                       return Command::UsePotionNE;
    if (cmd == "u nw")                       return Command::UsePotionNW;
    if (cmd == "u se")                       return Command::UsePotionSE;
    if (cmd == "u sw")                       return Command::UsePotionSW;
    // attack
    if (cmd == "a no")                       return Command::AttackNorth;
    if (cmd == "a so")                       return Command::AttackSouth;
    if (cmd == "a ea")                       return Command::AttackEast;
    if (cmd == "a we")                       return Command::AttackWest;
    if (cmd == "a ne")                       return Command::AttackNE;
    if (cmd == "a nw")                       return Command::AttackNW;
    if (cmd == "a se")                       return Command::AttackSE;
    if (cmd == "a sw")                       return Command::AttackSW;
    // stairs

    // control toggles
    if (cmd == "toggle_enhancements")         return Command::ToggleEnhancements;
    if (cmd == "q" || cmd == "quit")        return Command::Quit;
    if (cmd == "r" || cmd == "restart")     return Command::Restart;
    if (cmd == "f" || cmd == "freeze")     return Command::Freeze;
    return Command::Unknown;
}

}