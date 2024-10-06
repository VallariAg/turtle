# Turtle - Container Runtime

A lightweight container runtime created with Linux namespaces and cgroup.

Reference: https://codingchallenges.fyi/challenges/challenge-docker/#:~:text=This%20challenge%20is%20to%20build,packaging%20software%20into%20container%20images.


### Setup

1. Install deps:
```
sudo dnf install libcgroup-tools -y
```

2. Setup container fs:
```
wget https://dl-cdn.alpinelinux.org/alpine/v3.20/releases/x86_64/alpine-minirootfs-3.20.2-x86_64.tar.gz
mkdir /tmp/turtle-os
tar xzf alpine-minirootfs-3.20.2-x86_64.tar.gz --directory=/tmp/turtle-os/
```

3. Make shell script executable:
``` 
chmod +x turtle.sh turtle-sh.sh
```
 
### Use

There are two implimentations of this container: 
1. Single shell script 
    - `turtle-sh.sh` - sets up namespaces and cgroups in single shell script
2. C++ program and a shell script:
    - `turtle.sh` - sets up cgroups
    - `main.cpp` sets up namespaces.)


Run turtle container (with just a single shell script):
```
./turtle-sh.sh sh    // exec into container
./turtle-sh.sh ls    // run random commands
```

Run turtle container (with c++):
```
./turtle.sh run /bin/busybox sh       // exec into container
./turtle.sh run /bin/busybox ls       // run random commands
```


