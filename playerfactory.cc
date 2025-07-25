export module playerfactory;
import playercharacter;
import <memory>;
import <string>;

export class PlayerFactory {
 public:
    static std::unique_ptr<PlayerCharacter> createPlayer(const std::string &race);
};
