// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sig_handler(int signal){
	if(strsignal(signal) == "unknown signal" || strsignal(signal) == NULL){
		printf("strsignal error");
	}else{
		printf("Proces %d zakonczony sygnalem %d: %s\n",getpid(),signal,strsignal(signal));
	}

	exit(signal);
}

int main(int argc, char *argv[]){
	int pid = getpid();
	int signal_number = 2; // domyślny numer sygnału (SIGINT)
	int signal_action = 1; // domyślna opcja (wykonywanie operacji domyślnej)

	if(argc > 2){
		signal_number = atoi(argv[1]);
		signal_action = atoi(argv[2]);
	}

 	printf("PID: %d\n", pid);

	switch(signal_action){
		case 1:
			if(signal(signal_number, sig_handler) == SIG_ERR){ // obsługa sygnalu z argumentu
				perror("signal error: ");
				exit(EXIT_FAILURE);
			} 
			break;
		case 2:
			if(signal(signal_number, SIG_IGN) == SIG_ERR){ // ignorowanie sygnału z argumentu
				perror("signal error: ");
				exit(EXIT_FAILURE);
			} 
			break;
		case 3:
			if(signal(signal_number, SIG_DFL) == SIG_ERR){ // operacja domyślna sygnalu z argumentu
				perror("signal error: ");
				exit(EXIT_FAILURE);
			} 
			break;
		default:
			printf("Drugi argument nie moze byc > 3 lub < 0\n");
			return 0;
	}

	printf("Oczekiwanie sygnalu... \n");

	
while(1){
	pause();
}
	sleep(1);

	return 0;
}
