#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

int set_hostname() {
    char hostname[1024];
    gethostname(hostname,1024);
    // cout << "old hostname: " + string(hostname) + "\n";

    const char *new_hostname = "turtle";
    int rt = sethostname(new_hostname, 6);
    if (rt != 0) {
        return 1;
    }
    gethostname(hostname,1024);
    cout << "=> new hostname: " + string(hostname) + "\n";
    return 0;
}

int set_rootdir() {
    chdir("/tmp/turtle-os");
    return chroot("/tmp/turtle-os");
}


int mount_proc() {
    return system("mount proc /proc -t proc");
}

void create_ns() {
    auto uid = getuid();
    auto gid = getgid();
    int rt = unshare(CLONE_NEWUSER | CLONE_NEWPID | CLONE_NEWUTS | CLONE_NEWNS);
    if (rt != 0) {
        cout << "creating namespaces failed!" << endl;
    }
    std::ofstream uid_file("/proc/self/uid_map");
    uid_file << "0   " << uid << "   1";
    uid_file.close();

    std::ofstream setgroups("/proc/self/setgroups");
    setgroups << "deny" << endl;
    setgroups.close();

    std::ofstream gid_file("/proc/self/gid_map");
    gid_file << "0  " << gid << "  1";
    gid_file.close();

    cout << "=> new userid: " << getuid() << ", new gid: " << getgid() << "\n";
}

void setup() {
    int rt = set_rootdir();
    if (rt != 0) {
         cout << "failed to setup rootdir with chroot! \n";
         exit(EXIT_FAILURE);
    }
    rt = mount_proc();
    if (rt != 0) {
         cout << "failed to mount procfs! \n";
         exit(EXIT_FAILURE);
    }
    rt = set_hostname();
    if (rt != 0) {
         cout << "failed to setup hostname! \n";
         exit(EXIT_FAILURE);
    }
}

void teardown() {
    cout << "\n=> tearing down... \n";
    
    int rt = system("umount /proc");
    if (rt != 0) {
         cout << "failed to unmount procfs! \n";
         exit(EXIT_FAILURE);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Too few arguments, no command was passed! Try running `run <cmd>` \n";
        exit(EXIT_FAILURE);
    }
    create_ns();
    
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child process - needed for PID ns
        cout << ("=> Starting container...\n");
        setup();
        atexit(teardown);
        int rt = 0;

        if (string(argv[1]) == "run") {
            string command;
            for (int i=2; i<argc;i++){
                command += string(argv[i]) + " ";
            }
            cout << "running cmd: " + command + "\n";

            const char* char_command = command.c_str();
            rt = system(char_command);
            if (rt != 0) {
                cout << "!!! command failed !!! \n";
                return 1;
            }
        }  else {
            cout << "try running `run <cmd>`, nothing else works! :P \n";
        }
        exit(rt);
    } else {
        // parent process - should wait for child to die
        int status;
        waitpid(pid, &status, 0);
        int exit_code = WEXITSTATUS(status);
        if (exit_code != 0) {
            cout << "!!! command failed with exit code " << exit_code << " !!! \n";
            return 1;
        }
        cout << ("=> Exiting container...\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
}
