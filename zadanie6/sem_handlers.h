// Bohdan Fedirko
#ifndef _SEM_HANDLERS_H_
#define _SEM_HANDLERS_H_

#define MAX_LIB 20

struct lib_struct {
    char semaphore[20];
    int task;
    int val;
    sem_t sem_add;
};



extern sem_t* create_sem(const char* semaphore, int task, int val);

extern sem_t* open_sem(const char* semaphore);

extern int val_of_sem(sem_t* sem_add, int* val);

extern int post_sem(sem_t* sem_add);

extern int wait_sem(sem_t* sem_add);

extern int close_sem(sem_t* sem_add);

extern int rem_sem(const char* semaphore);

#endif
