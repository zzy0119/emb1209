
LDFLAGS+=-pthread

pool:main.o pool.o queue.o 
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm *.o pool



