// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


int main(int argc, char *argv[]){

	int signal_number = 2; // domyślny sygnał
	int signal_action = 1; // domyślne działanie
	if(argc > 2){
		signal_number = atoi(argv[1]);
		signal_action = atoi(argv[2]);
	}
	int pidc = getpid();
	if(setpgid(pidc,0) == -1){
		perror("setpgid error:");
	}
	int pgidc = getpgid(0);
	printf("PID: %d, PGID: %d\n", pidc,pgidc);
	if(signal(signal_number,SIG_IGN) == SIG_ERR){
		perror("signal error: ");
		exit(EXIT_FAILURE);
	}
	for(int i=0;i<3;i++){
	int child_pid = fork();
		switch(child_pid){
			case -1:
				perror("error during fork");
				exit(EXIT_FAILURE);
				break;
			case 0:
				sleep(i+1);
				printf("==========================CHILD \n");
				printf("PID: %d PGID: %d\n",getpid(), getpgid(getpid()));
					if(execlp("./a", "a", argv[1], argv[2], (char *) NULL) == -1){
						perror("execlp error: ");
						exit(EXIT_FAILURE);
						return 0;
					}
				break;
			default:
				break;
	}
}
	for(int i=0; i<3;i++){
		int status;
		wait(&status);
		printf("========================== \n");
		if(WIFSIGNALED(status)){
			int sig_num = WTERMSIG(status);
			printf("Proces zakonczony przez sygnal %d: %s\n", sig_num, strsignal(sig_num));
		}else if(WIFEXITED(status)){
			int sig_num = WTERMSIG(WEXITSTATUS(status));
			printf("Proces zakonczony przez sygnal %d: %s\n", sig_num, strsignal(sig_num));
			}
		}
	printf("==========================KONIEC: %d \n", getpid());
	sleep(1);
	return 0;
}
