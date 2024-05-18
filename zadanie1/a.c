// Bohdan Fedirko

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int uid = getuid();
    int gid = getgid();
    int pid =  getpid();
    int ppid = getppid();
    int pgid = getpgid(pid);

    printf("uid: %d\n", uid);
    printf("gid: %d\n", gid);
    printf("pid: %d\n", pid);
    printf("ppid: %d\n", ppid);
    printf("pgid: %d\n", pgid);

    return 0;
}
