import <iostream>;
import <string>;
import engine;

int main(int argc,char* argv[]) {
    std::string lf = argc>1?argv[1]:"default_floor.txt";
    cc3k::GameEngine eng{lf,0};
    eng.run();
    return 0;
}