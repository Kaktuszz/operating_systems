// Bohdan Fedirko
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "sem_handlers.h"
sem_t* g_sem;

int usleep(unsigned int usec);

void atexit_handler(){
        close_sem(g_sem);
}


int main(int argc, char *argv[]) {
        atexit(atexit_handler);
        sem_t* sem = open_sem(argv[1]);
        g_sem = sem;
        srand(time(NULL));
        //for (int i = 0; i < 3; i++) {
                usleep(rand()%3123412);
                assert(wait_sem(sem));
                usleep(rand()%124231);
                int s_val = 0;
                int file_r = open("numer.txt", O_RDONLY);
                if (file_r == -1) {
                        perror("\tFailed during opening file");
                        printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                        exit(EXIT_FAILURE);
                }

                ssize_t bytes_read;
                char buffer[32];
                int number;
                memset(buffer, 0, sizeof(buffer));

                if ((bytes_read = read(file_r, buffer, sizeof(buffer) - 1)) == -1) {
                        perror("\tFailed during read file");
                        printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                        exit(EXIT_FAILURE);
                }
                if(close(file_r)==-1){
                       perror("Failed during closing file");
                       printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                       exit(EXIT_FAILURE);
                }


                number = atoi(buffer);
                number++;
                printf("\tNUMBER: %d\n", number);
                usleep(rand()%5612359);

                int length = snprintf(NULL, 0, "%d", number);
                char number_str[length + 1];
                int file_w = open("numer.txt", O_WRONLY);

                snprintf(number_str, sizeof(number_str), "%d", number);

                if (write(file_w, number_str, length) == -1) {
                perror("\tFailed during writing to file");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                exit(EXIT_FAILURE);
                }
                if(close(file_w)==-1){
                        perror("Failed during closing file");
                        printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                        exit(EXIT_FAILURE);
                }
                val_of_sem(sem, &s_val);
                printf("\tsem value in PID %d: %d\n", getpid(), s_val);
                assert(post_sem(sem));
        //}



    return 0;
}

