//Scheduler thanks to Christina!

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "utils.h"

int curr_proc = 0;
int max_proc = 10;
int start_time[1<<20];
int finish_time[1<<20]; 
int qs[4][1 << 20];
int ts[4] = {0,0,0,0};
int blocked_procs[1<<20];
int blocked_times[1<<20];
int b_tail = 0;
int num_Out_Of_Time = 0;



typedef enum{false, true} bool;

FILE *fp;
int pos;
int remain;

void
proc_open(int n){

    char s[32];
    sprintf(s,"p%i",n);

    fp = fopen(s,"r+");
    if (!fp){
        printf("p%d ",n);
        printf ("Error no is : %d\n", errno);
        dam("File wasn't opened");
    }
    fseek(fp,10,0);
    fscanf(fp,"%i",&pos);
    fseek(fp,30,0);
    fscanf(fp,"%i",&remain);

}

void proc_close(){
    fseek(fp,10,0);
    fprintf(fp,"%9i",pos + 10);
    fseek(fp,30,0);
    fprintf(fp,"%9i",remain);
    fclose(fp);
}

int proc_exec(int n,int quant){
    int count   = 0;
    int i       = 0;
    int x;

    proc_open(n);
    fseek(fp,40+(pos <<2), 0);
    for(;;){
        if(fscanf(fp,"%i",&x) == EOF){  //process terminated
            count |= (1 << 29);
            break;
        }
        if (count > remain){    //process blocked
            count |= (1<< 28);
            break;
        }
        count += x;
        ++pos;
        if (count > quant){     //process timed out
            count |=(1<<30);
            break;
        }
        if (++i > 20){
                break;
        }
    }

    remain -= count;
    proc_close();

    return count;
}

int proc_get_priority(int n){
    int x;

    proc_open(n);
    fseek(fp,0, 0);
    fscanf(fp,"%i",&x);
    return x;
}

void
enq(int q,int n){
    qs[q][ts[q]++]=n;
}

void 
deq(int q,int p){
    qs[q][p] = qs[q][--ts[q]];
}

void 
deq_blocked(int q){
    //printf("tail is at %d\n",b_tail);

    blocked_procs[q] = blocked_procs[--b_tail];  
    blocked_times[q] = blocked_times[b_tail];
    
   // printf("blocked is size %d\n",b_tail);
}

void 
enq_blocked(int n, int time){
    blocked_times[b_tail] = time;
    blocked_procs[b_tail++] = n;
}


//four queues, each with a tail pointer
//start at head of each queue and schedule from head to tail
//use two four loops to do this.
//Have a queue that handles blocked processes

void queue_Proc(int time){
        //need to add what time it starts
        //printf("adding %d\n",curr_proc);
        enq(proc_get_priority(curr_proc),curr_proc);
        start_time[curr_proc] = time;
        ++curr_proc;
}
        

bool all_queues_empty(){
    //printf("%d %d %d %d\n",ts[0],ts[1],ts[2],ts[3]);
    return (ts[0] == 0 && ts[1] == 0 && ts[2] == 0 && ts[3] == 0);
}

bool blocked_empty(){
    return b_tail == 0;
}

bool has_procs(){
    return ((curr_proc < max_proc + 1) || !all_queues_empty() || !blocked_empty());
}

void print_blocked(){
    //printf("Blocked size is: %d\n",b_tail);
    for (int i = 0; i < b_tail; i++){
        printf("%d ",blocked_procs[i]);
    }
    printf("\n");
}


void unblock(int time){
    //printf("Running Unblock on queue length %d",b_tail);
    if (b_tail == 0) return;
    
    for (int i = 0; i < b_tail; i++){
        //printf("Curr blocked: ");
        //print_blocked();
        if (blocked_times[i] < time){
            //printf("%d is unblocked\n",blocked_procs[i]);
            int pri = proc_get_priority(blocked_procs[i]);
            enq(pri,blocked_procs[i]);
            deq_blocked(i);
            i--;
        }
    }
}

void print_queues(){
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < ts[i]; j++){
            printf("%d,",qs[i][j]);
        }
        printf("\n");
    }
}

long std_dev(int totalTime,int numProcs,int pri){
    long sum = 0;
    int avg = totalTime/numProcs;
    for (int i = 0; i < max_proc; i++){
        if(proc_get_priority(i) == pri){
            sum += pow(finish_time[i]-start_time[i]-avg,2);
        }
    }
    long var = sum/numProcs;
    return sqrt(var);
}


void print_stats(){
    __int64_t total_time[] = {0,0,0,0};
    int num_procs[] = {0,0,0,0};

    for (int i = 0; i <= max_proc; i++){
        int proc_pri = proc_get_priority(i);
        total_time[proc_pri] += finish_time[i] - start_time[i];
        //printf("Proc %d started at %d, ended at %d and took %d time\n",i,start_time[i],finish_time[i], finish_time[i] - start_time[i]);
        ++num_procs[proc_pri];
    }
    for(int i = 0; i < 4; i++){
        printf("The average time for the %d priority %d tasks is %ld us\n",num_procs[i],i,total_time[i]/num_procs[i]);
        printf("\t the standard deviation is %ld us\n",std_dev(total_time[i],num_procs[i],i));
    }

    printf("%d tasks ran out of time\n",num_Out_Of_Time);
}


void
schedule(){
    int x;
    int time =0;
    int currTime;
    //int pri[0,2,1,3,1,4,2,1,3,1,2,1]

    //Memory: keep track of memory and who it is (like blocked queue)
    //When you're out of memory, take someone out and put someone else in
    queue_Proc(0);

    while (has_procs()){
        //printf("At proc %d\n",curr_proc);
        currTime = time;
        unblock(currTime);
        if(all_queues_empty()){
                time += 1000;
        }
        else{
            for(int i = 0; i < 4; ++i){
            
                for (int j = 0;j < ts[i]; ++j){
                    
                    x = proc_exec(qs[i][j], 1000);
                    if          (x & (1 << 30)){            //process consumed quantum
                        if(i < 3){
                            enq(i+1,qs[i][j]);
                            deq(i,j) ; 

                        }
                        
                     //printf("%d consumes quantum\n",qs[i][j]);                                //dequeue and add to lower priority queue
                    }
                    else if     (x & (1 << 29)){            //process ended
                        //need to add an operation that writes finished time
                        int y = x & 0xfffff;
                        finish_time[qs[i][j]] = time + y;
                       // printf("%d Ended\n",qs[i][j]);
                        deq(i,j);                           //dequeue
                        
                        
                        
                    }
                    else if     (x & (1 << 28)){            //process blocked
                        enq_blocked(qs[i][j],time + random_between(400,1000));//needs to be a random number though

                        deq(i,j);    
                                              //dequeue and add to blocked queue
                    }
                    else if (remain <= 0){
                        deq(i,j);
                        ++num_Out_Of_Time;
                        //printf("something else happened to %d\n",qs[i][j]);
                    }
                    //add if it exceeds CPU limit
                
                    x &= 0xfffff;
                    time += x;
                }
            }    
        }
        //print_blocked();
        //print_queues();
        //printf("time = %d\n",time);

        if (curr_proc < max_proc+1){
            //printf("Current proc: %d\n",curr_proc);
            for(int i = 0; i < (time - currTime) / random_between(20,10000); i++){
                if (curr_proc > max_proc)
                    break;
                queue_Proc(time);
            }
        }    
    }
    
}

int main(){
    
    schedule();
    
    print_stats();

    return 0;
}