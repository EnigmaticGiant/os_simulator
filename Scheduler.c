#include <stdio.h>
#include <stdlib.h>
#include "Process.h"


#define totalProcess 10



Process* AllTheProcess[totalProcess];
Process* PriorityQs[4][totalProcess];
Process* BlockQueue[totalProcess];
int tailIndex[4] = {0};

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
    
/*
void Process(void){
int p[100];
int a[100];
int t[100];
int i = 0;

    while(1){
        while(!feof) {
            if(priority == -1 || address == -1 || ms == -1){
                printf("-1 -1 -1\n");                             //printing -1 -1 -1 to tell everything else to stahp
                exit(1);
            }
            p[i] = priority;
            a[i] = address;
            t[i] = ms;
            i++;
            scanf("%d %d %d", priority, address, ms);
            while(1){
                
            }

        }
    }

}
*/
void process_handler()
{
    while(1)          //Infinite Loop unless we are done, then we are going to stahp everything, so we are checking that these values are not -1, and if they are, we blow this popsicle stand and get some suckers.
    {
        while(priority != -9 || address != -9 || ms != -9)                         // FIFO LOOP
        {
            // CHECK IF THE FIRST THING READ IS (-1,-1,-1) BREAK LOOP;
            if(priority != -1 || address != -1 || ms != -1){
                printf("-1 -1 -1\n");
                exit(1);
            }
            // BLOCK QUEUE CHECK
                
            // READY QUEUE CHECK
            for(int i=0; i<3; i++)      //Priority based for loop
            {
                //PROCESS TILL YOU BLOCK IT
            }
            // PRINT FIFO CODE FOR SWITCH DISK TO SWITCH FROM READING TO WRITING
            // Close FIFO

            // CHECK IF EVERYTHING HAS BEEN PROCESSED
                // IF SO SEND (-1,-1,-1) TO DISK
            // OPEN FIFO FOR READING
        }
        // CHECK THE LAST THING READ FOR END CODE
    }
}





int main() 
{
    
    return 0;
}