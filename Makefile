CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
OBJS = sorted_list.o test_scheduler.o dlist.o priority_queue.o task.o uid.o scheduler.o


test : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test

scheduler.o : scheduler.c scheduler.h
	$(CC) $(CFLAGS) -c scheduler.c

test_scheduler.o : test_scheduler.c scheduler.h
	$(CC) $(CFLAGS) -c test_scheduler.c

uid.o : ../uid/uid.c ../uid/uid.h
	$(CC) $(CFLAGS) -c ../uid/uid.c

task.o : ../task/task.c ../task/task.h
	$(CC) $(CFLAGS) -c ../task/task.c

priority_queue.o : ../priority_queue/priority_queue.c  ../priority_queue/priority_queue.h
	$(CC) $(CFLAGS) -c  ../priority_queue/priority_queue.c

sorted_list.o : ../sorted_list/sorted_list.c ../sorted_list/sorted_list.h
	$(CC) $(CFLAGS) -c ../sorted_list/sorted_list.c

dlist.o : ../dlist/dlist.h ../dlist/dlist.c
	$(CC) $(CFLAGS) -c ../dlist/dlist.c

.PHONY : clean

clean :
	-rm test $(OBJS)
