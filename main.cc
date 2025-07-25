import <iostream>;
import <string>;
import engine;
import <cstdlib>;
import <ctime>;
int main(int argc,char* argv[]) {
    std::string lf = argc>1?argv[1]:"default_floor.txt";
    std::cout << lf << std::endl;
    std::srand(std::time(0));
    cc3k::GameEngine eng{lf,0};
    eng.run();
    return 0;
}