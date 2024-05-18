// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	FILE *file = fopen("add.txt","w");

	if(file == NULL){
		perror("error opening file");
		exit(EXIT_FAILURE);
	}


	int uid = getuid();
	int gid = getgid();
	int pid = getpid();
	int ppid = getppid();
	int pgid = getpgid(pid);
	printf("==========================PARENT: \n");

	printf("uid: %d\n", uid);
	printf("gid: %d\n", gid);
	printf("pid: %d\n", pid);
	printf("ppid: %d\n", ppid);
	printf("pgid: %d\n", pgid);

	fprintf(file,"==========================PARENT: \n");
	fprintf(file, "uid: %d\n", uid);
	fprintf(file, "gid: %d\n", gid);
	fprintf(file, "pid: %d\n", pid);
	fprintf(file, "ppid: %d\n", ppid);
	fprintf(file, "pgid: %d\n", pgid);


	for(int i=1;i<=3;i++){

	switch(fork()){
	case -1:
		perror("error during fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		sleep(i+1);
		int uidc = getuid();
		int gidc = getgid();
		int pidc = getpid();
		int ppidc = getppid();
		int pgidc = getpgid(pidc);
		
		printf("==========================CHILD: %d\n",i);		
		printf("uid: %d\n", uidc);
		printf("gid: %d\n", gidc);
		printf("pid: %d\n", pidc);
		printf("ppid: %d\n", ppidc);
		printf("pgid: %d\n", pgidc);;

		fprintf(file, "==========================CHILD: %d\n",i);;
		fprintf(file, "uid: %d\n", uidc);
		fprintf(file, "gid: %d\n", gidc);
		fprintf(file, "pid: %d\n", pidc);
		fprintf(file, "ppid: %d\n", ppidc);
		fprintf(file, "pgid: %d\n", pgidc);
		
		break;
	default:

		break;

		}

	}

	fclose(file);
	sleep(10);
	return 0;
}
