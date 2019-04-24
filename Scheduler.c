#include <stdio.h>
#include <stdlib.h>
#include "Process.h"


#define totalProcess 100



Process* AllTheProcess[totalProcess];
Process* PriorityQs[4][totalProcess];
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
    









int main() 
{
    
    return 0;
}