# Turtle - Container Runtime

https://codingchallenges.fyi/challenges/challenge-docker/#:~:text=This%20challenge%20is%20to%20build,packaging%20software%20into%20container%20images.


Setup:
```
wget https://dl-cdn.alpinelinux.org/alpine/v3.20/releases/x86_64/alpine-minirootfs-3.20.2-x86_64.tar.gz
mkdir /tmp/turtle-os
tar xzf alpine-minirootfs-3.20.2-x86_64.tar.gz --directory=/tmp/turtle-os/
    
chmod +x turtle.sh
```
Run turtle container:
```
./turtle.sh run /bin/busybox sh
```


