#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "utils.h"

typedef struct 
{
	int r_w;				// Binary values 0: Read, 1: Write (DEFAULT: 0)
	int ms;					// Time
	int address;			// Address /Index
	int priority;			// Priority of the process range: 0-3
}InstBlock;
typedef struct 
{
	int LRU[256];
	int D_Loc[256];			// Disk Location
	int M_Loc[256];			// Memory Location
	int P_used;				// Pages Remaining (DEFAULT: 100)
}PageTable;
typedef struct 
{
	InstBlock I_Block;
	PageTable P_Table;
}Process;

Process createProcess ()
{
	Process proc;
	proc.I_Block.r_w		= 0;
	proc.I_Block.address 	= 0;
	proc.I_Block.priority 	= random_between(0,3);
	proc.P_Table.P_used		= 100;
	for(int i = 0; i< 256;i++)
	{
		proc.P_Table.LRU[i] 	= 0;
		proc.P_Table.D_Loc[i] 	= 0;
		proc.P_Table.M_Loc[i] 	= 0;
	}
	return proc;
} 


int main()
{
	Process proc= createProcess();
	printf("%i %i %i %i\n",proc.I_Block.r_w,proc.I_Block.address,proc.I_Block.priority,proc.P_Table.P_used);
}