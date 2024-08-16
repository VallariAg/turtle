# How to build:

#### step 0
Download the alpine iso file (for testing while development) --- Read till the end of the section

Mount alpine on a directory. I create a `os` dir under the project root and unmounted apline.
```
isoinfo -i alpine-standard-3.20.2-x86.iso -l       # list contents of iso file

sudo mount -o loop alpine-standard-3.20.2-x86.iso os/       -> is read-only, why??
sudo umount os/
```
That didn't work! Let's just extract for now:
```
sudo yum install p7zip p7zip-plugins
cd os/
7z x ../alpine-standard-3.20.2-x86.iso
```

NEVERMIND, I downloaded the wrong thing!
Download mini root fs from https://www.alpinelinux.org/downloads/ (not iso files).
```
7z x ../alpine-minirootfs-3.20.2-x86_64.tar
```

#### step 1
1. Run command line commands from c++: https://linux.die.net/man/3/system
system call supports only c's strings? why?

#### step 2
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

#### step 3
To isolate process -> change container's root fs
Make the alphine fs as container's root.

