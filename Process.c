#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "utils.h"
#include <assert.h>

 struct InstBlock{
	int r_w;				// Binary values 0: Read, 1: Write (DEFAULT: 0)
	int ms;					// CPU Time. How much time this process is allowed 
	int address;			// Address /Index
	int priority;			// Priority of the process range: 0-3
};

 struct PageTable {
	int LRU[256];
	int D_Loc[256];			// Disk Location
	int M_Loc[256];			// Memory Location
	int P_remain;				// Pages Remaining (DEFAULT: 100)
};

struct Process{
	InstBlock* I_Block;
	PageTable* P_Table;
	// Needed to identify the process itself. Process number is assigned in the process generator.
	int processNumber;  
};

InstBlock *getInstBlock(Process *proc){
	return proc->I_Block;
}

PageTable *getPageTable(Process *proc){
	return proc->P_Table;
}

int getRW(InstBlock *pt){
	return pt->r_w;
}

void setRW(InstBlock *pt, int num){
	pt->r_w = num;
}

int getMS(InstBlock *pt){
	return pt->ms;
}

void setMS(InstBlock *pt, int num){
	pt->ms = num;
}

int getAddress(InstBlock *pt){
	return pt->address;
}

void setAddress(InstBlock *pt, int num){
	pt->address = num;
}

int getPriority(InstBlock *pt){
	return pt->priority;
}

int getLRUindex(PageTable *ib, int index){
	return ib->LRU[index];
}

void setLRUindex(PageTable *ib, int index, int num){
	ib->LRU[index] = num;
}

int getDLoc(PageTable *ib, int index){
	return ib->D_Loc[index];
}

void setDLoc(PageTable *ib, int index, int num){
	ib->D_Loc[index] = num;
}

int getMloc(PageTable *ib ,int index){
	return ib->M_Loc[index];
}

void setMloc(PageTable *ib, int index, int num){
	ib->M_Loc[index] = num;
}

int getPRemain(PageTable *ib){
	return ib->P_remain;
}

void setPRemain(PageTable *ib, int num){
	ib->P_remain = num;
}

InstBlock* createInstBlock() {
	InstBlock * p = malloc(sizeof(InstBlock));
	p->address = 0;
	p->ms = random_between(0,100);
	p->priority = random_between(0,3);
	p->r_w = 0;
	return p;
}

PageTable* createPageTable() {
	PageTable *p = malloc(sizeof(PageTable));
	for(int i =0; i < 256; i++) {
		p->D_Loc[i] = 0;
		p->M_Loc[i] = 0;
		p->LRU[i] = 0;
	}
	p->P_remain = 100;
   return p;
}

Process* createProcess() {
	Process *p = malloc(sizeof(Process));
	p->I_Block = createInstBlock();
	p->P_Table = createPageTable();
	return p;
}








