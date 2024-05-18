// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


int main(int argc, char *argv[]){

	printf("==========================PARENT \n");
	int pid = getpid();
	int signal_number = 2; // domyślny sygnał
	int signal_action = 1; // domyślne działanie
	if(argc > 2){
		signal_number = atoi(argv[1]);
		signal_action = atoi(argv[2]);
	}

	printf("pid: %d\n", pid);

	int child_pid = fork();

		switch(child_pid){
			case -1:
				perror("Error during fork");
				exit(EXIT_FAILURE);
				break;
			case 0:
				printf("==========================CHILD \n");
				if(execlp("./c_1", "c_1", argv[1], argv[2], (char *) NULL) == -1){
				perror("execlp");
				exit(EXIT_FAILURE);
				}
				break;
			default:
					sleep(5);
					if(kill(child_pid, 0) != 0){
						perror("Process does not exist");
						exit(EXIT_FAILURE);
					}
					if(killpg(child_pid, signal_number)==-1){
						perror("killpg error: ");
						exit(EXIT_FAILURE);
					}
				int status;
				wait(&status);
				if(WIFSIGNALED(status)){
					int sig_num = WTERMSIG(status);
					printf("Proces: %d zakonczony przez sygnal: %d: %s\n", child_pid, sig_num, strsignal(sig_num));
				}else if(WIFEXITED(status)){
					int sig_num = WEXITSTATUS(status);
					printf("Proces: %d zakonczony z exit kodem: %d\n", child_pid, sig_num);
				}
				break;
		}
	return 0;
}
