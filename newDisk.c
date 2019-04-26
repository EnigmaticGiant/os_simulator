#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <time.h> 

int qi = 0;
int count = 0;
//fpos_t position;
//file pointers named after respective files
FILE *s_requests;
FILE *d_results;

//this is the structure the files use and how we are storing each request (an instance per request)
typedef struct {
    int time;
    int location;
    int ID;
}request;

request* q[10000];
request* tempBlock;

request* createRequest(int *diskRequest)
{
    request *newRequest = malloc(sizeof(request));
    newRequest->time = diskRequest[0];
    newRequest->location = diskRequest[1];
    newRequest->ID = diskRequest[2];

    return newRequest;
}


void enq(request* block) {
        q[qi++] = block;
}

request* deq(int pos) {
        request* temp = q[pos];
        q[pos] = q[--qi];
        return temp;
}

// void load_q(int time) {

//     request block;
//     block.time = -1;
//     //static rec_un x;
//     //int loc;
//     //int proc;

//     if (block.time>time){
//         time = block.time;
//         //fseek(s_requests, count-1, 0);
//     } 

//     while(block.time <= time){

//         if(block.time>=0){
//             //printf("after process: time = %d, location = %d, ID = %d\n", block.time, block.location, block.ID);
//         	enq(block);
//         }
// 		//for each line, wee have 3 numbers in the following format:
//         // time location ID
//         fscanf(s_requests, "%d %d %d\n", &block.time, &block.location, &block.ID);  
//         //printf("time = %d, location = %d, ID = %d\n", block.time, block.location, block.ID);
//         tempBlock.time = block.time;
//         tempBlock.location = block.location;
//         tempBlock.ID = block.ID;
    
//     }

//     return;        

     
// }


//this function helps simulate a disk actuator for each process call, you alternate between tha smallest and biggest function
int smallest() {
    int sp = 0;
    int i;
    for(i = 1; i<qi; i++){
        if(q[i].ID < q[sp].ID) {
            sp = i;
        }
    }
    return sp;
}
//also helps simulate the disk actuator like said above.
int largest() {
    int  yi= 0;
    int i;
    for(i = 1; i<qi; i++){
        if(q[i].ID > q[yi].ID){
            yi = i;
        }
    }
    return yi;
}
//secondary driver to main.
int process(int time) {
    int static dir = 0;

    if (dir == 0){

        while(qi){
            request* newBlock;
            newBlock = deq(smallest());
            time = time+5;
            // fprintf(d_results, "%d %d\n", time, newBlock->ID);
        }
    }
    else{
        while(qi){
            request *newBlock;
            newBlock = deq(largest());
            time = time+5;
            // fprintf(d_results, "%d %d\n", time, newBlock->ID);
        }


    }
    dir ^= 1;
    //enq(tempBlock);
    return time;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

int main() {
    // open fifo pipe ----------------------------------------------
    int fd1;
    char* myfifo = "/tmp/myfifo";

    // declaring variables -----------------------------------------
    
    int diskRequest[3], requestFulfilled[3];
    // int endRequest[3] = {"0", "0", "0"};
    int diskTime = 0;

    
    // ACTUAL OPERATION OF DISK ------------------------------------

    while(1)
    {
        fd1 = open(myfifo,O_RDONLY);
        read(fd1,diskRequest,12);
        diskTime = diskRequest[0];
        while(diskRequest[0] != -9)
        {            
            read(fd1,diskRequest,12);
            request *newRequest = createRequest(diskRequest);
            enq(newRequest);
        }
        diskTime = process(diskTime);
        close(fd1);

        fd1 = open(myfifo,O_WRONLY);
        while(/*things to return in q*/)
        {
            request* returnRequest = deq(/*don't know what this pos is*/);
            requestFulfilled[0] = returnRequest->time;
            requestFulfilled[1] = returnRequest->location;
            requestFulfilled[2] = returnRequest->ID;
            write(fd1,requestFulfilled,12);
        }
        close(fd1);
        waitFor(2);


    }
    return 0;
}





