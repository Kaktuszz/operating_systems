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
				perror("error during fork");
				exit(EXIT_FAILURE);
				break;
			case 0:
				printf("==========================CHILD \n");
				if(execlp("./a", "a", argv[1], argv[2], (char *) NULL) == -1){
					perror("execlp");
					exit(EXIT_FAILURE);
				}
				break;
			default:
				sleep(1);
				if(kill(child_pid,0)!=0){
					perror("Process does not exist");
					exit(EXIT_FAILURE);
				}
				if(kill(child_pid, signal_number) == -1){
					perror("kill error");
					exit(EXIT_FAILURE);
				}

				int status;
				wait(&status);
				printf("==========================PARENT \n");
				if(WIFSIGNALED(status)){// sprawdzam czy proces potomny zakończony przez sygnał
					int sig_num = WTERMSIG(status);
					printf("Proces %d zakonczony przez sygnal %d: %s\n", child_pid, WTERMSIG(status), strsignal(WTERMSIG(status)));
				}else if(WIFEXITED(status)){ // sprawdzam z jakim statusem był zakończony proces potomny
					int sig_num = WEXITSTATUS(status); // konwertuje exit status na numer sygnału
					printf("Proces: %d zakonczony z exit kodem: %d, przez sygnal: %d: %s\n", child_pid,status, sig_num, strsignal(WTERMSIG(sig_num)));
				}

				break;
		}
	return 0;
}
