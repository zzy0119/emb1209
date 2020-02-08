
# CFLAGS遍历编译器编译的时候自动加载 LDFLAGS制定库路径
CFLAGS+=-I. 
LDFLAGS+=-lsysstu -L.

OBJ=main
SRC=main.o 

$(OBJ):$(SRC)
	@gcc -o $@ $^ $(LDFLAGS)

clean:
	@rm main main.o 
