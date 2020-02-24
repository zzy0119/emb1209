CFLAGS+=-D_XOPEN_SOURCE
LDFLAGS+=-lcrypt

pwd:passwd.o
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)
