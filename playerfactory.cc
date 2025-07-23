export module playerfactory;
import playercharacter;
import <memory>;
import <string>;

export class PlayerFactory {
 public:
    static std::unique_pointer<Player> createPlayer(const std::string &race);
};
