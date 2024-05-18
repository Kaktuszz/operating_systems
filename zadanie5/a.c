// Bohdan Fedirko
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#define BUF_SIZE 4

char **pipe_arg;

void sig_ign_handler(int signal){
        if(strsignal(signal) == "unknown signal" || strsignal(signal) == NULL){
                printf("signal error: ");
        }else{
                printf("Process zakonczony sygnalem %d: %s\n",signal,strsignal(signal));
        }
        printf("Usuwanie potoku\n");

        if(unlink(pipe_arg[1])==-1){
                perror("Blad przy usunieciu potoku: ");
        }else{
                printf("Potok: %s poprawnie usuniety\n",pipe_arg[1]);
        }
        exit(EXIT_FAILURE);
}

void exit_handler(){
        if(unlink(pipe_arg[1]) == -1){
                perror("Blad przy usunieciu potoku: ");
        }else{
                printf("Potok: %s poprawnie usuniety\n", pipe_arg[1]);
        }
}

int main(int argc, char *argv[]) {

        if (argc != 4) {
                fprintf(stderr, "Wpisz: %s [bufor][plik_wejsciowy][plik_wyjsciowy]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        pipe_arg = argv;

        if (mkfifo(argv[1],0644) == -1) { // tworzę potok
                perror("Creating pipe error");
                exit(EXIT_FAILURE);
        }

        if(signal(SIGINT,sig_ign_handler) == SIG_ERR){
                perror("signal error: ");
                exit(EXIT_FAILURE);
        }


        char programs[][8] = {"kons","prod"};

        for(int i=0;i<=1;++i){
                char way[8];
                strcat(way, "./");
  		strcat(way, programs[i]);
                int child_pid = fork();
                switch(child_pid){
                        case -1:
                                perror("Fork error: ");
                                exit(EXIT_FAILURE);
                        case 0:
                                if(execlp(way,programs[i],argv[1],argv[2],argv[3], (char *) NULL)==-1){
                                        perror("execlp");
                                        exit(EXIT_FAILURE);
                                }
                                break;
                        default:
                }
                memset(way, '\0', sizeof(way));
        }

        for(int i=0;i<=1;i++){
                wait(NULL);
        }
        if(atexit(exit_handler) !=0){
                perror("atexit error: ");
                exit(1);
        }
    return 0;
}
