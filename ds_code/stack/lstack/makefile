CFLAGS+=-I/home/zhangzongyan/ds/emb1209/ds_code/llist2
LDFLAGS+=-lllist -L/home/zhangzongyan/ds/emb1209/ds_code/llist2

lstack:main.o lstack.o
	gcc -o $@ $^ $(LDFLAGS)

lstack.o:lstack.c
	gcc -c -o $@ $^ $(LDFLAGS)

clean:
	rm *.o lstack
