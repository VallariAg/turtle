# This started out as a "guide" but now it's a documentation of the choatic process of building this project:

This contains mistakes, tricks, concepts, links, and questions.

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
That doesn't make files in ./os/bin executable for some reason. And no `chmod +x os/bin` did not work (it changed permission but it was still not executable).

Do this to extract it:
```
wget https://dl-cdn.alpinelinux.org/alpine/v3.20/releases/x86_64/alpine-minirootfs-3.20.2-x86_64.tar.gz
tar xzf alpine-minirootfs-3.20.2-x86_64.tar.gz --directory=/tmp/turtle-os/
```
This worked as I wanted! What is wrong with the 7z tool!?

#### step 1
1. Run command line commands from c++: https://linux.die.net/man/3/system
system call supports only c's strings? why?

what even is char**? it points to the memory where the memory of char variable is stored? why would we wanna use char**??

#### step 2
2. container hostname with namespaces! 
    - https://man7.org/linux/man-pages/man7/namespaces.7.html
    - https://benjamintoll.com/2022/08/08/on-unsharing-namespaces-part-one/

`unshare` - used to create new namespaces:
1. command line tool man page: https://man7.org/linux/man-pages/man1/unshare.1.html
2. system call man page: https://man7.org/linux/man-pages/man2/unshare.2.html

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

What is the difference between a "hostname" and "username"?

#### step 3
To isolate process (from host fs) -> change container's root fs
Make the alphine fs as container's root.

#### step 4
To isolate process (from host process) - container process can't see/interact host processes

Tasks:
1. create PID namespace
2. mount /proc (use `mount`) & umount when container terminates
3. isolate this new mount from host fs: create mount namespace & `unshare` mount namespace


Questions:
1. what does mounting a fs mean? why do we do it?
2. why mount /proc?
3. why do I need to mount proc twice? one time with unshare and then inside container?
4. why new mount namespace?
5. why exactly is it necassary to create PID ns + mount ns + mount proc? what happens when I don't do one of these?


Links:
- https://www.unix.com/unix-for-beginners-questions-and-answers/280445-linux-containers-proc-mounting-other-queries.html
- https://www.redhat.com/sysadmin/7-linux-namespaces

#### step 5

Run container rootless. 
1. create new User namespace (--user) 
2. set the mappings between the users on the host and container (--map-root-user)

Links:
- https://man7.org/linux/man-pages/man7/user_namespaces.7.html
- https://man7.org/linux/man-pages/man1/unshare.1.html
- https://raesene.github.io/blog/2016/02/04/Docker-User-Namespaces/


https://man7.org/linux/man-pages/man2/fork.2.html - example at button on how to use it in c++