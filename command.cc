export module command;
import <string>;
namespace cc3k{

export enum class Command {
    // Movement
    MoveNorth, MoveSouth, MoveEast, MoveWest,
    MoveNE, MoveNW, MoveSE, MoveSW,
    
    // Actions
    UsePotionNorth, UsePotionSouth, UsePotionEast, UsePotionWest,
    UsePotionNE, UsePotionNW, UsePotionSE, UsePotionSW,

    AttackNorth, AttackSouth, AttackEast, AttackWest,
    AttackNE, AttackNW, AttackSE, AttackSW,
    // Race selection
    SelectShade, SelectDrow, SelectVampire, SelectTroll, SelectGoblin,
    // Control
    Quit, Restart,
    ToggleEnhancements,
    Unknown,
    // Freeze
    Freeze
};
export class CommandInterp{
public:
    CommandInterp() = default;
    Command parse(const std::string& cmd) const;
};

}
