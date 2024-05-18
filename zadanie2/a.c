// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
        char *dir_path = malloc(strlen(argv[1])+3);
        sprintf(dir_path, "./%s", argv[1]);

        printf("==========================PARENT \n");
                int uid = getuid();
                int gid = getgid();
                int pid = getpid();
                int ppid = getppid();
                int pgid = getpgid(ppid);

                 if(pgid == -1){
                        perror("pgid error");
                        exit(EXIT_FAILURE);
                }

                printf("uid: %d\n", uid);
                printf("gid: %d\n", gid);
                printf("pid: %d\n", pid);
                printf("ppid: %d\n", ppid);
                printf("pgid: %d\n", pgid);


        for(int i=1;i<=3;i++){
                switch(fork()){
                        case -1:
                                perror("error during fork");
                                exit(EXIT_FAILURE);
                                break;
                        case 0:
                                if(execlp(dir_path, argv[1],(char *) NULL) == -1){
                                        perror("execlp");
                                        exit(EXIT_FAILURE);
                                }
                                break;

                        default:
                                wait(NULL);
                                break;
                }
        }



        free(dir_path);

        return 0;
}
