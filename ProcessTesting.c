#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include <assert.h>

/***
 *  The functions here tests all the functions written in "Process.c" .
 * Simple copy the main fucntion in process.c to double check
 * Note : You cannot simply run this file as you can never malloc process* outside of the file it was created.
 ***/

int main() {
	Process * p = createProcess();
	InstBlock *inst = getInstBlock(p);
	PageTable* t = getPageTable(p);
	setRW(inst,1); // Write
	assert(getRW(inst) ==1);
	setMS(inst,88);
	assert(getMS(inst) == 88);
	setAddress(inst,88);
	assert(getAddress(inst) == 88);
	setLRUindex(t,1,88);
	assert(getLRUindex(t,1) == 88);
	setDLoc(t,1,88);
	assert(getDLoc(t,1) == 88);
	setMloc(t,1,88);
	assert(getMloc(t,1) == 88);
	setPRemain(t,88);
	assert(getPRemain(t) == 88);
	return 0;
}


