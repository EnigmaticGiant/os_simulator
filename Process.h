#ifndef PROCESS__
#define PROCESS__

typedef struct Process Process;
typedef struct PageTable PageTable;
typedef struct InstBlock InstBlock;

extern InstBlock *getInstBlock(Process *);
extern PageTable *getPageTable(Process *);
extern int getRW(InstBlock *);
extern void setRW(InstBlock *, int );
extern int getMS(InstBlock *);
extern void setMS(InstBlock *, int );
extern int getAddress(InstBlock *);
extern void setAddress(InstBlock *, int );
extern int getPriority(InstBlock *);
extern int getLRUindex(PageTable *ib, int);
extern void setLRUindex(PageTable *ib, int, int );
extern int getDLoc(PageTable *ib, int);
extern void setDLoc(PageTable *ib, int, int );
extern int getMloc(PageTable *ib ,int);
extern void setMloc(PageTable *ib, int, int );
extern int getPRemain(PageTable *);
extern void setPRemain(PageTable *, int );
extern Process* createProcess (); 

// functions needed to modify processes added here

#endif