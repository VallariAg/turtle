# Turtle - Container Runtime

https://codingchallenges.fyi/challenges/challenge-docker/#:~:text=This%20challenge%20is%20to%20build,packaging%20software%20into%20container%20images.

```
g++ -o turtle main.cpp

// run one of these:
./turtle run ls                     // to run on host system
sudo unshare -u ./turtle run ls     // to run on UTS namespace with "turtle" hostname
```
