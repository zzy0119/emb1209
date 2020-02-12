CFLAGS+=-I../stack/stack/ -I../queue/queue/

STACK=../stack/stack/stack.o 
QUEUE=../queue/queue/queue.o

hw2_11:hw2_11.o $(STACK) $(QUEUE)
	gcc -o $@ $^

ball:ball.o $(STACK) $(QUEUE)
	gcc -o $@ $^

clean:
	rm *.o hw2_11

