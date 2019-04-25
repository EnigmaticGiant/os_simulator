#include "Disk.h"
#include <stdio.h>
#include <stdlib.h>

long q[10000];
int qi = 0;
int count = 0;
//fpos_t position;
//file pointers named after respective files
FILE *s_requests;
FILE *d_results;

typedef struct {
           int loc : 30;
           int proc : 30;
} rec;

typedef union {
        rec x;
        long y;
} rec_un;

void inq(long n) {
        q[qi++] = n;
}

long deq(int pos) {
        long r = q[pos];
        q[pos] = q[--qi];
        return r;
}

void load_q(int time) {
    static int t = -1;
    static rec_un x;
    int loc;
    int proc;
    while(t<=time){
        if(t>=0){
        	inq(x.y);
        }
		//for each line, wee have 3 numbers in the following format:
        // time location ID
        fscanf(s_requests, "%d %d %d\n", &t, &loc, &proc);
        x.x.loc = loc;
        x.x.proc = proc;
    }        

    if (t>time){
        time = t;
        //fseek(s_requests, count-1, 0);
    }  
}
//this function helps simulate a disk actuator for each process call, you alternate between tha smallest and biggest function
int smallest() {
    int sp = 0;
    int i;
    for(i = 1; i<qi; i++){
        if(q[i] < q[sp]) {
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
        if(q[i] > q[yi]){
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
            rec_un y;
            y.y = deq(smallest());
            time = time+5;
            fprintf(d_results, "%d %d\n", time, y.x.proc);
        }
    }
    else{
        while(qi){
            rec_un y;
            y.y = deq(largest());
            time = time+5;
            fprintf(d_results, "%d  %d\n", time, y.x.proc);
        }


    }
    dir ^= 1;
	printf("Qi:%i\n",qi);
    return time;
}


int main() {
    int time = 0;

    s_requests = fopen("s_requests.txt", "r");
    d_results = fopen("d_results.txt", "w");


    if(s_requests == NULL){
        printf("Error: file could not open\n");
        exit(1);
    }

    fscanf(s_requests, "%3i", &time);
    
    fseek(s_requests, 0, 0);
	//printf("time is %d\n", time);
    while(!feof(s_requests)){
        //printf("entered end of file checker\n");
        load_q(time);
        time = process(time);
    }
    fclose(s_requests);
    fclose(d_results);

}