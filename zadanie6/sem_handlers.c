// Bohdan Fedirko
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <fcntl.h>
#include "sem_handlers.h"

sem_t* create_sem(const char* semaphore, int val, int task){
        sem_t* sem = sem_open(semaphore, O_CREAT | O_EXCL, 0644, val, task);
        if(sem == SEM_FAILED){ // O_EXCL creates only one file for 2 proccesses
                perror("Failed during creating semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                rem_sem(semaphore);
                return NULL;
        }else{
                printf("Semaphore: %s with adress: %p | Successfully created\n", semaphore, (void *)sem);
                return sem;
        }
}

sem_t* open_sem(const char* semaphore){
        sem_t* sem = sem_open(semaphore, O_EXCL);
        if(sem == SEM_FAILED){
                perror("Failed during opening semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return NULL;
        }else{
                printf("Semaphore: %s with address: %p | Successfully opened\n", semaphore, (void *)sem);
                return sem;
        }
}

int val_of_sem(sem_t *sem_add, int *val){
        if(sem_getvalue(sem_add, val) == -1){
                perror("Failed during getting value of semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return 0;
        }else{
                //printf("Current value of semaphore %p: %d\n", sem_add, *val);
                return 1;
        }
}

int post_sem(sem_t *sem_add){
        if(sem_post(sem_add) == -1){
                perror("Failed during UP semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return 0;
        }else{
                //printf("Semaphore is upped\n");
                return 1;
        }
}

int wait_sem(sem_t *sem_add){
        if(sem_wait(sem_add) == -1){
                perror("Failed during LOWERING semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return 0;
        }else{
                //printf("Semaphore is lowered\n");
                return 1;
  }
}

int close_sem(sem_t *sem_add){
        if(sem_close(sem_add) == -1){
                perror("Failed during closing semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return 0;
        }else{
                printf("Semaphore successfully closed\n");
                return 1;
        }
}

int rem_sem(const char* semaphore){
        if(sem_unlink(semaphore) == -1){
                perror("Failed during removing semaphore");
                printf("Line: %d\nFile: %s\n", __LINE__, __FILE__);
                return 0;
        }else{
                printf("Semaphore: %s is removed\n", semaphore);
                return 1;
        }
}


