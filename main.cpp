#include <stdlib.h>
#include <iostream>
#include <unistd.h>
using namespace std;

void set_hostname() {
    char hostname[1024];
    gethostname(hostname,1024);
    // cout << "old hostname: " + string(hostname) + "\n";

    const char *new_hostname = "turtle";
    sethostname(new_hostname, 6);
    gethostname(hostname,1024);
    cout << "new hostname: " + string(hostname) + "\n";
}

int set_rootdir() {
    chdir("/tmp/turtle-os");
    return chroot("/tmp/turtle-os");
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Too few arguments, no command was passed! Try running `run <cmd>` \n";
        return 1;
    }
    int rt = set_rootdir();
    if (rt != 0) {
         cout << "failed to setup rootdir with chroot! \n";
         return 1;
    }
    set_hostname();

    if (string(argv[1]) == "run") {
        string command;
        for (int i=2; i<argc;i++){
            command += string(argv[i]) + " ";
        }
        cout << "running cmd: " + command + "\n";
        
        const char* char_command = command.c_str();
        int rt = system(char_command);
        if (rt != 0) {
            cout << "!!! command failed !!! \n";
            return 1;
        }
    }  else {
        cout << "try running `run <cmd>`, nothing else works! :P \n";
    }
    return 0;
}
