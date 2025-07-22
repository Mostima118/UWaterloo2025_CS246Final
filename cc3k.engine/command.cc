export module command;
import <string>;
namespace cc3k{

export enum class Command {
    // Movement
    MoveNorth, MoveSouth, MoveEast, MoveWest,
    MoveNE, MoveNW, MoveSE, MoveSW,
    UpStairs, DownStairs,
    // Actions
    UsePotionNorth, UsePotionSouth, UsePotionEast, UsePotionWest,
    AttackNorth, AttackSouth, AttackEast, AttackWest,
    // Race selection
    SelectShade, SelectDrow, SelectVampire, SelectTroll, SelectGoblin,
    // Control
    Quit, Restart,
    ToggleEnhancements,
    Unknown
};
export class CommandInterp{
public:
    CommandInterp() = default;
    Command parse(const std::string& cmd) const;
};

}
