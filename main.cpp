#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Too few arguments, no command was passed! Try running `run <cmd>` \n";
        return 0;
    }

    if (string(argv[1]) == "run") {
        string command;
        for (int i=2; i<argc;i++){
            command += string(argv[i]) + " ";
        }
        cout << "running cmd: " + command + "\n";
        
        const char* char_command = command.c_str();
        system(char_command);
    }  else {
        cout << "try running `run <cmd>`, nothing else works! :P \n";
    }
    return 0;
}
