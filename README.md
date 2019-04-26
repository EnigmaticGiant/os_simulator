# CS 300: Operating Systems

This is an implementation of a simulated process scheduler that communicates with a simulated hard drive disk.

## Features
* Process.c
* Scheduler.c 
* Disk.c

### Process.c
This file generates "processes," simulated by structs. They represent processes in an operating system and are used by the Scheduler and Disk to demonstrate functionality. 

NOTE: Must be compiled with "utils.c" and "utils.h"

### Scheduler.c
This file simulates a process scheduler within an operating system. After (1) generating processes, the Scheduler then (2) assigns priority to each one and stages the processes for running via placement in a series of queues, then (3) finally runs the processes in order. The Scheduler accounts for blocking and for other issues.

### Disk.c
This file simulates a disk. It receives disk requests from the Scheduler and processes them, then returns the desired data. In order to simulate a rotating disk, it returns data in an alternating order of largest to smallest, then smallest to largest, etc.

### FIFO
Process communication between the Scheduler and Disk is handled using FIFO.

## Notes from study sessions
![board2](https://user-images.githubusercontent.com/43188896/56602206-8f13a180-65c2-11e9-9a1f-00fd3b4378c9.jpg)
![board1](https://user-images.githubusercontent.com/43188896/56602216-920e9200-65c2-11e9-820e-53b9aa5cc54d.jpg)
