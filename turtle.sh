g++ -o turtle main.cpp

# ./turtle run ls                  # to run on host system
# sudo unshare -u ./turtle "$@"    # to run on UTS namespace with "turtle" hostname
# sudo unshare -u ./turtle /bin/busybox "$@"  
sudo unshare -upfm --mount-proc ./turtle "$@" 
