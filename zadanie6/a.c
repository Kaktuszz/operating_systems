// Bohdan Fedirko
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "sem_handlers.h"
sem_t* global_sem;
const char* semaphore = "sem";

void sig_ign_handler(int signal){
        if(strcmp(strsignal(signal), "unknown signal") == 0 || strsignal(signal) == NULL){
                printf("signal error: ");
        }else{
                printf("Process zakonczony sygnalem %d: %s\n",signal,strsignal(signal));
        }
        rem_sem(semaphore);
        printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
        exit(EXIT_FAILURE);
}

void atexit_handler(){
        rem_sem(semaphore);
}


int main(int argc, char *argv[]){
        atexit(atexit_handler);
        if(signal(SIGINT, sig_ign_handler) == SIG_ERR){
                perror("Signal error");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }

        if(argc != 4){
                printf("How to use program: \n %s [program_name] [processes_number] [num_critical_sections]\n", argv[0]);
                return 0;
        }

        char* prog_name = argv[1];
        int process_num = atoi(argv[2]);
        int critical_sections = atoi(argv[3]);

        if(process_num < 1 || critical_sections < 1){
                printf("Critical section/number of processes should be > 0\n");
                return 0;
        }

        int file = open("numer.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(file == -1){
                perror("Failed during opening/creating file");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }
        if(write(file,"0" ,1) == -1){
                perror("Failed during writing to file");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }
        if(close(file) == -1){
                perror("Failed during closing file");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }

        sem_t* sem = create_sem(semaphore, critical_sections, 1);
        global_sem = sem;
        int s_val = 0;
        val_of_sem(sem, &s_val);
        printf("Semaphore address: %p, Value: %d\n", (void *)sem,s_val);
        int pids[process_num];
        char way[8];
        strcat(way, "./");
        strcat(way, prog_name);
        for(int i=0; i<process_num; i++){
                pids[i] = fork();
                switch(pids[i]){
                        case -1:
                                perror("Failed during fork");
                                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                                exit(EXIT_FAILURE);
                                break;
                        case 0:
                                execlp(way, prog_name, semaphore, (char *) NULL);
                                break;
                        default:
                                break;

                }
        }
        int status[process_num];
        memset(way, '\0', sizeof(way));
        for(int i=0;i<process_num; i++){
                waitpid(pids[i],&status[i], 0);
        }



        ssize_t bytes_read;
        char buffer[32];
        memset(buffer, 0, sizeof(buffer));
        file = open("numer.txt", O_RDONLY);
        if(file == -1){
                perror("Failed during opening");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }
        if ((bytes_read = read(file, buffer, sizeof(buffer) - 1)) == -1) {
                perror("Failed during read file");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
        }
        int number = atoi(buffer);
        if(number == process_num){
                printf("Processes successfully synchronized\nProcess number: %d \nNumber from file: %d\n", process_num, number);
        }else{
                printf("Something went wrong \nProcess number: %d \nNumber from file: %d\n", process_num, number);
        }
        close(file);

        return 0;
}
