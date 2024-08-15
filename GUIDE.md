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



