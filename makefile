OBJS = scheduler.o process.o utils.o
OBKS = disk.o process.o utils.o
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g

all: scheduler diskMan process

scheduler	: $(OBJS)
	gcc $(LOPTS) $(OBJS) -o scheduler

diskMan		: $(OBJS)
	gcc $(LOPTS) $(OBKS) -o diskMan

process		: $(OBJS)
	gcc $(LOPTS) process.o -o process

scheduler.o	: Scheduler.c Scheduler.h utils.h
	gcc $(OOPTS) Scheduler.c

disk.o 		:

process.o 	: Process.c Process.h utils.h
	gcc $(OOPTS) Process.c

utils.o 	: utils.c utils.h
	gcc $(OOPTS) utils.c

schedule	: scheduler
	./schedule

disk		: diskMan
	./disk

clean		:
	rm -f *.o schedule disk