// C program to implement one side of FIFO 
// This side writes first, then reads 
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
    int fd; 
  
    // FIFO file path 
    char * myfifo = "/tmp/myfifo"; 
  
    // Creating the named file(FIFO) 
    // mkfifo(<pathname>, <permission>) 
    // printf("here");
    // fflush(stdout);
    mkfifo(myfifo, 0666); 
//   printf("there");
//   fflush(stdout);
    // char arr1[80], arr2[80]; 
    int move[3], newMove[3];
    // move[0] = 0, move[1] = 13, move[2] = 191;
    // printf("here");
    // fflush(stdout);
    while (1) 
    { 
        // printf("here");
        // fflush(stdout);
        // Open FIFO for write only 
        fd = open(myfifo, O_WRONLY); 
  
        // Take an input arr2ing from user. 
        // 80 is maximum length 
        // fgets(arr2, 80, stdin);
  
        // Write the input arr2ing on FIFO 
        // and close it 

        fgets(move, 12, stdin);
        
        write(fd, move, 12); 
        close(fd); 
  
        // Open FIFO for Read only 
        fd = open(myfifo, O_RDONLY); 
  
        // Read from FIFO 
        read(fd, newMove, 12); 
  
        // Print the read message 
        printf("time: %i, loc: %i, id: %i\n", newMove[0], newMove[1], newMove[2]); 
        close(fd);
        waitFor(2);
    } 
    return 0; 
} 