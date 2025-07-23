module human;
// need import gold

Human::Human() : Enemy{140, 20, 20 'H', "Human"} {}

int Human::dropGold() const {
    return 0; // no gold automatically added, spawning of gold piles handled in engine
}
