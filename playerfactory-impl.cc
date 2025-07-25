module playerfactory;
import playercharacter;
import shade;
import drow;
import vampire;
import troll;
import goblin;
import <memory>;
import <string>;

using namespace std;

unique_ptr<PlayerCharacter> PlayerFactory::createPlayer(const string &race) {
    if (race == "s") {
        return make_unique<Shade>(125, 125, 25, 25, '@', "Player", "Shade");
    } else if (race == "d") {
        return make_unique<Drow>(150, 150, 25, 15, '@', "Player", "Drow");
    } else if (race == "v") {
        return make_unique<Vampire>(50, 0, 25, 25, '@', "Player", "Vampire");
    } else if (race == "t") {
        return make_unique<Troll>(120, 120, 25, 15, '@', "Player", "Troll");
    } else if (race == "g") {
        return make_unique<Goblin>(110, 110, 15, 20, '@', "Player", "Goblin");
    }
    return nullptr;
}
