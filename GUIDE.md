# How to build:

0. Download the alpine iso file (for testing while development) 
Mount alpine on a directory. I create a `os` dir under the project root and unmounted apline.
```
isoinfo -i alpine-standard-3.20.2-x86.iso -l       # list contents of iso file

sudo mount -o loop alpine-standard-3.20.2-x86.iso os/       -> is read-only, why??
sudo unmount os/
```
That didn't work! Let's just extract for now:
```
sudo yum install p7zip p7zip-plugins
cd os/
7z x ../alpine-standard-3.20.2-x86.iso
```
1. Run command line commands from c++: https://linux.die.net/man/3/system
system call supports only c's strings? why?

2. container hostname with namespaces! 
    - https://man7.org/linux/man-pages/man7/namespaces.7.html
    - https://benjamintoll.com/2022/08/08/on-unsharing-namespaces-part-one/

```
sudo unshare --uts turtle<binary!> 

// cleanup 
mount | grep "turtle"
sudo umount /path/to/mount

ps aux | grep "turtle"
kill -9 <pid>
```

"lsns" lists all namespaces and it's filled with chrome tabs. 
Why do broswers put each tab in its own namepace??

