g++ -o turtle main.cpp

# ./turtle run ls                  # to run on host system
# sudo unshare -u ./turtle "$@"    # to run on UTS namespace with "turtle" hostname
# sudo unshare -u ./turtle /bin/busybox "$@"   
# sudo unshare -upfm --mount-proc ./turtle "$@" 
# unshare --user --map-root-user -upfm --mount-proc ./turtle "$@" 
export PATH=$PATH:/bin
export PS1="\\u@\\h ~ "

cgroup_setup(){
    CGROUP_NAME="test"
    if [ ! -d "/sys/fs/cgroup/$CGROUP_NAME/tasks" ]; then
        echo ">> setting cgroup..."
        if [ ! -d "/sys/fs/cgroup/$CGROUP_NAME" ]; then
            echo ">> creating '$CGROUP_NAME' cgroup"
            sudo mkdir /sys/fs/cgroup/$CGROUP_NAME
            sudo bash -c "echo +cpu > /sys/fs/cgroup/$CGROUP_NAME/cgroup.subtree_control"
            sudo bash -c "echo +memory > /sys/fs/cgroup/$CGROUP_NAME/cgroup.subtree_control"
        fi
        echo ">> creating $CGROUP_NAME/tasks cgroup"
        sudo mkdir /sys/fs/cgroup/$CGROUP_NAME/tasks
    fi
    sudo bash -c "echo 50 > /sys/fs/cgroup/$CGROUP_NAME/tasks/cpu.weight"
    sudo bash -c "echo "500M" > /sys/fs/cgroup/$CGROUP_NAME/tasks/memory.max"

    TURTLE_PID=$(echo $$)
    sudo bash -c "echo $TURTLE_PID > /sys/fs/cgroup/$CGROUP_NAME/tasks/cgroup.procs"
}

cgroup_setup
./turtle "$@"
