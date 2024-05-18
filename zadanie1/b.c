// Bohdan Fedirko

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	printf("==========================PARENT \n");
		int uid = getuid();
		int gid = getgid();
		int pid = getpid();
		int ppid = getppid();
		int pgid = getpgid(ppid);

		printf("uid: %d\n", uid);
		printf("gid: %d\n", gid);
		printf("pid: %d\n", pid);
		printf("ppid: %d\n", ppid);
		printf("pgid: %d\n", pgid);


	for(int i=1;i<=3;i++){

	switch(fork()){
	case -1:
		perror("error during fork");
		exit(EXIT_FAILURE);
		break;
	case 0:
		int uidc = getuid();
		int gidc = getgid();
		int pidc = getpid();
		int ppidc = getppid();
		int pgidc = getpgid(ppidc);
		int pgrpc = getpgrp();
		
		printf("==========================CHILD %d\n",i);
		printf("uid: %d\n", uidc);
		printf("gid: %d\n", gidc);
		printf("pid: %d\n", pidc);
		printf("ppid: %d\n", ppidc);
		printf("pgid: %d\n", pgidc);

		break;
	default:
		wait(NULL);
		break;

}
}

	return 0;
}
