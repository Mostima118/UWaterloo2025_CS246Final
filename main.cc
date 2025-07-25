import <iostream>;
import <string>;
import engine;
import <cstdlib>;
import <ctime>;
import <fstream>;
int main(int argc,char* argv[]) {
    std::string lf = argc>1?argv[1]:"default_floor.txt";
    
    std::ifstream fin;
    do {
        fin.open(lf);
        if (!fin.is_open()) {
            std::cout << "Cannot open file " << lf << ". Please enter a new filename: " << std::endl;
            std::getline(std::cin, lf);
        }
    } while (!fin.is_open());

    std::srand(std::time(0));
    cc3k::GameEngine eng{lf,0};
    eng.run();
    return 0;
}