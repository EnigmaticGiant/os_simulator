// Process need to be fix 
/*
    time_requested need to be something like time_blocked_at
    pages needs to be a array of pagerTable with a max of 100 
    P_remain needs to be removed
    add max iteration to proccess.c
    add stats
        - for hit rate (which is calculated by if a process page faults / overwrites a memory location (i think))
*/

// If something doesnt make sense or you need me to explain what i mean by my comment call me (7579513754), texting/groupme might be missed

#include <stdio.h>
#include <stdlib.h>
#include "Process.h"


#define totalProcess 10



Process* AllTheProcess[totalProcess];
Process* PriorityQs[4][totalProcess];
Process* BlockQueue[totalProcess];          
int tailIndex[4] = {0};                         // 0-3 Priority 

void generateProcessess(void) {
    for (int i = 0; i < totalProcess; i++) {
        AllTheProcess[i] = createProcess();
    }
    return;
}

void putProcessintoPQ(void) {
    for (int i = 0; i < totalProcess; i++) {
        InstBlock * instB = getInstBlock(AllTheProcess[i]);
        if (getPriority(instB) == 0) {
            PriorityQs[0][tailIndex[0]++] = AllTheProcess[i];
        }
        else if (getPriority(instB) == 1) {
            PriorityQs[1][tailIndex[1]++] = AllTheProcess[i];
        }
        else if (getPriority(instB) == 2) {
            PriorityQs[2][tailIndex[2]++] = AllTheProcess[i];
        }
        else {
            PriorityQs[3][tailIndex[3]++] = AllTheProcess[i];
        }
        }
    
    return;
    }
    
/* CREATE A ENQ AND DEQ FUNCTION */

void process_handler()
{
    static int address =1;
    static int scheduler_global_time =0;
    while(1)
    {
        for(int i=0; i < totalProcess; i++)
        {
            // If BlockQueue[i]->time_blocked_at <= scheduler_global_time      
            // Deq into respected priority queue
        }
        // SKIPING READY QUEUE SINCE FIFO IS NOT INCLUDED
        for(int i=0;i<4;i++)    // Priority Queue Loop
        {
            for(int j=0; j<tailIndex[i]; j++)
            {
                while(/* Proccess pages are not 0 */)
                {
                    // Generate a random number to simulate I/O instructions (whatever the numbers where called for the files in the first project)
                    // After sometime, create a new page and add a new address to the memory location 
                    // Check if it goes over max iteration (something from the first project)
                }
                if(/* If all the pages have been used */)
                {
                    // access the LRU get and put the information onto disk
                    if(/* If there is something already in the disk location and it is not the same address */)
                    {
                        // "Perform 2 disk operation"
                        // Update the LRU
                        // add 5ms to each process that was effect by the disk requests (ie set time in processes equal to scheduler_global_time then for the first +5ms and the second gets +10ms)
                    }
                    else
                    {
                        // move mem_address to disk_address and insert new address into mem_address
                    }
                }
                //continue to next process
            }
        }
        // Add a random about to the scheduler_global_time
    }
}

int main() 
{
    
    return 0;
}