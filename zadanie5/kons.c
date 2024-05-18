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
        int pipe = open(argv[1],O_RDONLY);
        int file = open(argv[3],O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(pipe == -1){
                perror("Error opening pipe file");
                exit(EXIT_FAILURE);
        }

        if(file == -1){
                perror("Error opening file");
                exit(EXIT_FAILURE);
        }
        char bufer[BUF_SIZE];
        int bytes_read;
        char newline = '\n';
        char text[12] = "Konsument: ";
        while((bytes_read = read(pipe, bufer, sizeof(bufer))) > 0){
                if (write(file, bufer, bytes_read) != bytes_read) {
                        perror("Writing to file error");
                        exit(EXIT_FAILURE);
                }
                if((write(STDOUT_FILENO, text, 12)) == -1 || (write(STDOUT_FILENO, bufer, bytes_read)) == -1 || write(STDOUT_FILENO, &newline, 1) == -1){
                        perror("Error writing to console");
                        exit(EXIT_FAILURE);
                }

                usleep(rand() % 10289);


        }


        if(close(file) == -1 || close(pipe) == -1){
                perror("Closing file error");
                exit(EXIT_FAILURE);
        }


        return 0;
}