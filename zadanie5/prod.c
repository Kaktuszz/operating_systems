// Bohdan Fedirko
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_SIZE 4


int main(int argc, char *argv[]) {
        srand(time(NULL));
        int pipe = open(argv[1],O_WRONLY);
        int file = open(argv[2],O_RDONLY);
        if(pipe == -1){
                perror("Error opening pipe file");
                exit(EXIT_FAILURE);
        }

        if(file == -1){
                perror("Error opening file");
                exit(EXIT_FAILURE);
        }
        char bufer[BUF_SIZE+2];
        int bytes_read;
        char newline = '\n';
        char text[12] = "Producent: ";
        while((bytes_read = read(file,bufer,BUF_SIZE+2))>0){
                if(write(pipe,bufer,bytes_read)!=bytes_read){
                        perror("Error writing to pipe");
                        exit(EXIT_FAILURE);
                }
                if((write(STDOUT_FILENO, &text, 12)) == -1 || (write(STDOUT_FILENO, bufer, bytes_read)) == -1 || write(STDOUT_FILENO, &newline, 1) == -1){
                        perror("Error writing to console");
                        exit(EXIT_FAILURE);
                }
                usleep(rand() % 910872);
        }
        if(close(file) == -1 || close(pipe) == -1){
                perror("Closing file/pipe error");
                exit(EXIT_FAILURE);

        }
        return 0;
}
