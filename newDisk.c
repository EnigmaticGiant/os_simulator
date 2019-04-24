#include <stdio.h>
#include <stdlib.h>

//Initializing queue index and communication file pointers
int qi = 0;
FILE *s_requests;
FILE *d_results;

//Structure created to store each request. Used in process queue below.
typedef struct {
    int time;
    int location;
    int ID;
}request;

//Initialized the queue of requests and the storage structs for each request as it comes in 
//tempBlock is used to save requests for enqueue-ing in the future when the time didn't fit the condition at the moment
request q[10000];
request tempBlock;
request block;


//Adds a request struct to the process queue
void enq(request block) {
        q[qi++] = block;
}

//Returns and deletes a request struct from the process queue
request deq(int pos) {
        request temp = q[pos];
        for (int i = pos; i < qi - 1; i++) {
            q[i] = q[i+1];
        }
        qi -= 1;
        return temp;
}

//Loads scanned requests into the process queue. Saves them in tempBlock so they can be enqueued later if they don't get enqueued in the while loop here
//Updates global time if needed
void load_q(int time) {

    static int t = -1;

    if (block.time>time){
        time = block.time;
    } 

    while(block.time <= time){

        if(t>=0) {
        	enq(tempBlock);
        }
    
        fscanf(s_requests, "%d %d %d\n", &block.time, &block.location, &block.ID);  
        tempBlock.time = block.time;
        tempBlock.location = block.location;
        tempBlock.ID = block.ID;
        t = 1;
    
    }

    return;        

     
}
//Retrieves the position of the smallest address in the process queue
int smallest() {
    int sp = 0;
    int i;
    for(i = 1; i<qi; i++){
        if(q[i].location < q[sp].location) {
            sp = i;
        }
    }
    return sp;
}
//Retrieves the position of the largest address in the process queue
int largest() {
    int  yi= 0;
    int i;
    for(i = 1; i<qi; i++){
        if(q[i].location > q[yi].location){
            yi = i;
        }
    }
    return yi;
}
//Processes the process queue 
//simulates disk retrievals from outside to inside (smallest address to largest address) 
    //and inside to outside(largest address to smallest address)
//Updates global time
int process(int time) {

    int static dir = 0;

    if (dir == 0){

        while(qi){
            request newBlock;
            newBlock = deq(smallest());
            time = time + 5;
            fprintf(d_results, "%d %d\n", time, newBlock.location);
        }
    }
    else{
        while(qi){
            request newBlock;
            newBlock = deq(largest());
            time = time+5;
            fprintf(d_results, "%d %d\n", time, newBlock.location);
        }


    }
    dir ^= 1;
    return time;
}


int main() {

    int time = 0;
    block.time = -1;

    s_requests = fopen("s_requests.txt", "r");
    d_results = fopen("d_results.txt", "w");


    if(s_requests == NULL){
        printf("Error: file could not open\n");
        exit(1);
    }

    fscanf(s_requests, "%3i", &time);   //Initializes global time
    
    fseek(s_requests, 0, 0);            //Starts again at the beginning of the file

    while(!feof(s_requests)){
        load_q(time);                   //Continually loads and processes requests until file is at its end
        time = process(time);
    }
    if (tempBlock.time != 0) {          //Enqueues and processes request if left unqueued in load function
        enq(tempBlock);
        time = process(time);
    }
    fclose(s_requests);
    fclose(d_results);

}
