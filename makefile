all: OS_program3.o sched_sim.o
	gcc OS_program3.o sched_sim.o -o output -lpthread

OS_program3.o: OS_program3.c sched_sim.h
	gcc -c OS_program3.c 

sched_sim.o: sched_sim.c sched_sim.h
	gcc -c sched_sim.c
clean:
	rm *.o output

