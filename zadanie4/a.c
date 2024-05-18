// Bohdan Fedirko
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_SIZE 4

void producent(int filedes, const char *file_name) {

    	int file = open(file_name, O_RDONLY); // file = desktyptor pliku
    	if (file == -1) {
        	perror("Error opening file for reading");
        	exit(EXIT_FAILURE);
    	}

    	char bufer[BUF_SIZE+2];
    	int bytes_read;
		char buf_int[10];
    	while ((bytes_read = read(file,bufer,BUF_SIZE+2)) > 0) { // bytes_read - liczba rzeczywiscie odczytanych bajtow (zwraca funkcja read/write)
        	if (write(filedes, bufer, bytes_read) != bytes_read) { // sprawdzam czy odczytana liczba bajtow = zapisanym
            	perror("Error writing to pipe");
            	exit(EXIT_FAILURE);
        	}
		sprintf(buf_int, "%d", bytes_read);
		printf("\n");
		write(STDOUT_FILENO, bufer, bytes_read);
		//write(STDOUT_FILENO, buf_int, sizeof(buf_int));  // miałem wypisywać za pomocą write ale wypisuje bajty i symbole
		printf("\n Wczytano: %s\n",buf_int);
        	usleep(rand() % 910872);
    	}
	
	if(close(file) == -1 || close(filedes) == -1){
		perror("Closing file error");
		exit(EXIT_FAILURE);
	}
}

void konsument(int filedes, const char *file_name) {
    	int file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
    	if (file == -1) {
        	perror("Opening file for writing error");
        	exit(EXIT_FAILURE);
    	}

    	char bufer[BUF_SIZE];
    	int bytes_read;
		char buf_int[10];
    	while ((bytes_read = read(filedes, bufer, BUF_SIZE)) > 0) {
        	if (write(file, bufer, bytes_read) != bytes_read) {
            	perror("Writing to file error");
            	exit(EXIT_FAILURE);
        	}
		sprintf(buf_int, "%d", bytes_read); // konwertuje int w char
		printf("\n");
		write(STDOUT_FILENO, bufer, bytes_read);
		//write(STDOUT_FILENO, buf_int, sizeof(buf_int)); // miałem wypisywać za pomocą write ale wypisuje bajty i symbole
		printf("\n Wczytano: %s\n",buf_int);
        	usleep(rand() % 10289); // przytszymuje na losowy czas w mikrosekundach
    	}

    	if(close(file) == -1 || close(filedes) == -1){
		perror("Closing file error");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
    	if (argc != 3) {
        	fprintf(stderr, "Wpisz: %s [plik_wejsciowy] [plik_wyjsciowy]\n", argv[0]);
        	exit(EXIT_FAILURE);
    	}

    	srand(time(NULL));

    	int filedes[2]; 
    	if (pipe(filedes) == -1) { // tworzę potok
        	perror("Creating pipe error");
        	exit(EXIT_FAILURE);
    	}

    	int child_pid = fork();
    	switch(child_pid){
        	case -1:
            		perror("Fork error: ");
            		exit(EXIT_FAILURE);
        	case 0:
           		close(filedes[1]);
            		konsument(filedes[0], argv[2]);
            		break;
        	default:
           		close(filedes[0]);
            		producent(filedes[1], argv[1]);
            		wait(NULL);
    	}

    	return 0;
}
