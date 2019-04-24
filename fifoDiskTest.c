// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <time.h> 
  
int
random_between(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int main() 
{ 
    int fd1; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>,<permission>) 
    // printf("here");
    // fflush(stdout);
    // mkfifo(myfifo, 0666); 
    // printf("there");
    // fflush(stdout);
    // char str1[80], str2[80]; 
    int move[3], newMove[3];
    move[0] = 0, move[1] = 13, move[2] = 191;
    // printf("here");
    // fflush(stdout);
    while (1) 
    { 
        //printf("here");
        // fflush(stdout);
        // First open in read only and read 
        fd1 = open(myfifo,O_RDONLY); 
        read(fd1, move, 12); 
  
        // Print the read string and close
        move[0] = move[0] + 5; 
        printf("time: %i, loc: %i, id: %i\n", move[0], move[1], move[2]);  
        close(fd1); 

        // Now open in write mode and write 
        // string taken from user. 
        fd1 = open(myfifo,O_WRONLY); 
        // fgets(str2, 80, stdin);
        newMove[0] = move[0]; 
        newMove[1] = move[1]; 
        newMove[2] = move[2]; 
        write(fd1, newMove, 12); 
        close(fd1);
        waitFor(2);
    } 
    return 0; 
} 