import <iostream>;
import <string>;
import engine;

int main(int argc, char* argv[]) {
    
    std::string layoutFile;            // empty => randomized
    unsigned seed = 0;                 // 0 => time-based seed

    cc3k::GameEngine engine{layoutFile, seed};
    engine.run();
    return 0;
}
