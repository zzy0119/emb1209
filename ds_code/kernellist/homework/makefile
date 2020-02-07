
# CFLAGS遍历编译器编译的时候自动加载 LDFLAGS制定库路径
CFLAGS+=-I. 

OBJ=main
SRC=main.o student.o

# 目标:依赖文件
$(OBJ):$(SRC)
	# 规则
	@gcc -o $@ $^

# 伪目标
clean:
	@rm main main.o student.o
